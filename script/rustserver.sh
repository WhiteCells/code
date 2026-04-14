#!/usr/bin/env bash

set -euo pipefail

BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RUN_DIR="${BASE_DIR}/run"
LOG_DIR="${BASE_DIR}/logs"
ENV_FILE="${BASE_DIR}/.env"

HBBS_BIN="${BASE_DIR}/hbbs"
HBBR_BIN="${BASE_DIR}/hbbr"
HBBR_ARGS=()

HBBS_PID_FILE="${RUN_DIR}/hbbs.pid"
HBBR_PID_FILE="${RUN_DIR}/hbbr.pid"
HBBS_LOG_FILE="${LOG_DIR}/hbbs.log"
HBBR_LOG_FILE="${LOG_DIR}/hbbr.log"

usage() {
  cat <<'EOF'
Usage:
  ./start.sh start [hbbs|hbbr|all]
  ./start.sh stop [hbbs|hbbr|all]
  ./start.sh restart [hbbs|hbbr|all]
  ./start.sh status [hbbs|hbbr|all]
  ./start.sh log [hbbs|hbbr|all]

Defaults to "all" when no service name is provided.

.env example:
  HBBS_RELAY_HOST=158.178.243.225
  HBBS_RELAY_PORT=20012
EOF
}

ensure_dirs() {
  mkdir -p "${RUN_DIR}" "${LOG_DIR}"
}

load_env() {
  if [[ -f "${ENV_FILE}" ]]; then
    set -a
    # shellcheck disable=SC1090
    source "${ENV_FILE}"
    set +a
  fi
}

hbbs_args() {
  local relay_host="${HBBS_RELAY_HOST:-}"
  local relay_port="${HBBS_RELAY_PORT:-}"

  if [[ -z "${relay_host}" || -z "${relay_port}" ]]; then
    echo "hbbs: HBBS_RELAY_HOST or HBBS_RELAY_PORT is not set in ${ENV_FILE}" >&2
    return 1
  fi

  printf '%s\n' "-r" "${relay_host}:${relay_port}"
}

is_running() {
  local pid_file="$1"

  if [[ ! -f "${pid_file}" ]]; then
    return 1
  fi

  local pid
  pid="$(<"${pid_file}")"

  if [[ -z "${pid}" ]]; then
    return 1
  fi

  if kill -0 "${pid}" 2>/dev/null; then
    return 0
  fi

  rm -f "${pid_file}"
  return 1
}

start_service() {
  local name="$1"
  local bin="$2"
  local pid_file="$3"
  local log_file="$4"
  shift 4
  local args=("$@")

  if [[ ! -x "${bin}" ]]; then
    echo "${name}: binary not found or not executable: ${bin}" >&2
    return 1
  fi

  if is_running "${pid_file}"; then
    echo "${name}: already running (pid $(<"${pid_file}"))"
    return 0
  fi

  : > "${log_file}"
  nohup "${bin}" "${args[@]}" >>"${log_file}" 2>&1 &
  local pid=$!
  echo "${pid}" > "${pid_file}"
  sleep 1

  if kill -0 "${pid}" 2>/dev/null; then
    echo "${name}: started (pid ${pid})"
    return 0
  fi

  echo "${name}: failed to start, check ${log_file}" >&2
  rm -f "${pid_file}"
  return 1
}

stop_service() {
  local name="$1"
  local pid_file="$2"

  if ! is_running "${pid_file}"; then
    echo "${name}: not running"
    return 0
  fi

  local pid
  pid="$(<"${pid_file}")"
  kill "${pid}" 2>/dev/null || true

  for _ in {1..10}; do
    if ! kill -0 "${pid}" 2>/dev/null; then
      rm -f "${pid_file}"
      echo "${name}: stopped"
      return 0
    fi
    sleep 1
  done

  kill -9 "${pid}" 2>/dev/null || true
  rm -f "${pid_file}"
  echo "${name}: stopped forcefully"
}

status_service() {
  local name="$1"
  local pid_file="$2"
  local log_file="$3"

  if is_running "${pid_file}"; then
    echo "${name}: running (pid $(<"${pid_file}")) log=${log_file}"
  else
    echo "${name}: stopped"
  fi
}

log_service() {
  local service="${1:-all}"

  ensure_dirs

  case "${service}" in
    hbbs)
      touch "${HBBS_LOG_FILE}"
      tail -n 100 -F "${HBBS_LOG_FILE}"
      ;;
    hbbr)
      touch "${HBBR_LOG_FILE}"
      tail -n 100 -F "${HBBR_LOG_FILE}"
      ;;
    all)
      touch "${HBBS_LOG_FILE}" "${HBBR_LOG_FILE}"
      tail -n 100 -F "${HBBS_LOG_FILE}" "${HBBR_LOG_FILE}"
      ;;
    *)
      echo "Unknown service: ${service}" >&2
      usage
      return 1
      ;;
  esac
}

dispatch() {
  local action="$1"
  local service="${2:-all}"
  local hbbs_runtime_args=()

  ensure_dirs
  if [[ "${action}" == "start" || "${action}" == "restart" ]]; then
    mapfile -t hbbs_runtime_args < <(hbbs_args)
  fi

  case "${action}:${service}" in
    start:hbbs)
      start_service hbbs "${HBBS_BIN}" "${HBBS_PID_FILE}" "${HBBS_LOG_FILE}" "${hbbs_runtime_args[@]}"
      ;;
    start:hbbr)
      start_service hbbr "${HBBR_BIN}" "${HBBR_PID_FILE}" "${HBBR_LOG_FILE}" "${HBBR_ARGS[@]}"
      ;;
    start:all)
      start_service hbbs "${HBBS_BIN}" "${HBBS_PID_FILE}" "${HBBS_LOG_FILE}" "${hbbs_runtime_args[@]}"
      start_service hbbr "${HBBR_BIN}" "${HBBR_PID_FILE}" "${HBBR_LOG_FILE}" "${HBBR_ARGS[@]}"
      ;;
    stop:hbbs)
      stop_service hbbs "${HBBS_PID_FILE}"
      ;;
    stop:hbbr)
      stop_service hbbr "${HBBR_PID_FILE}"
      ;;
    stop:all)
      stop_service hbbs "${HBBS_PID_FILE}"
      stop_service hbbr "${HBBR_PID_FILE}"
      ;;
    restart:hbbs)
      stop_service hbbs "${HBBS_PID_FILE}"
      start_service hbbs "${HBBS_BIN}" "${HBBS_PID_FILE}" "${HBBS_LOG_FILE}" "${hbbs_runtime_args[@]}"
      ;;
    restart:hbbr)
      stop_service hbbr "${HBBR_PID_FILE}"
      start_service hbbr "${HBBR_BIN}" "${HBBR_PID_FILE}" "${HBBR_LOG_FILE}" "${HBBR_ARGS[@]}"
      ;;
    restart:all)
      stop_service hbbs "${HBBS_PID_FILE}"
      stop_service hbbr "${HBBR_PID_FILE}"
      start_service hbbs "${HBBS_BIN}" "${HBBS_PID_FILE}" "${HBBS_LOG_FILE}" "${hbbs_runtime_args[@]}"
      start_service hbbr "${HBBR_BIN}" "${HBBR_PID_FILE}" "${HBBR_LOG_FILE}" "${HBBR_ARGS[@]}"
      ;;
    status:hbbs)
      status_service hbbs "${HBBS_PID_FILE}" "${HBBS_LOG_FILE}"
      ;;
    status:hbbr)
      status_service hbbr "${HBBR_PID_FILE}" "${HBBR_LOG_FILE}"
      ;;
    status:all)
      status_service hbbs "${HBBS_PID_FILE}" "${HBBS_LOG_FILE}"
      status_service hbbr "${HBBR_PID_FILE}" "${HBBR_LOG_FILE}"
      ;;
    log:hbbs|log:hbbr|log:all)
      log_service "${service}"
      ;;
    *)
      echo "Unknown action or service: ${action} ${service}" >&2
      usage
      return 1
      ;;
  esac
}

main() {
  if [[ $# -lt 1 ]]; then
    usage
    exit 1
  fi

  load_env
  dispatch "$1" "${2:-all}"
}

main "$@"
