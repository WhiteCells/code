CC := gcc
CFLAGS := -Wall -Wextra -O2 -Icommon
BUILD_DIR := build
COMMON := common/net_utils.c

TARGETS := \
	$(BUILD_DIR)/tcp_echo_server \
	$(BUILD_DIR)/tcp_echo_client \
	$(BUILD_DIR)/udp_echo_server \
	$(BUILD_DIR)/udp_echo_client \
	$(BUILD_DIR)/nonblocking_accept_demo \
	$(BUILD_DIR)/select_echo_server \
	$(BUILD_DIR)/poll_echo_server \
	$(BUILD_DIR)/epoll_echo_server \
	$(BUILD_DIR)/epoll_buffered_echo_server \
	$(BUILD_DIR)/length_prefixed_codec_demo \
	$(BUILD_DIR)/thread_per_connection_echo_server \
	$(BUILD_DIR)/reactor_threadpool_demo \
	$(BUILD_DIR)/multi_reactor_demo

.PHONY: all clean

all: $(TARGETS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/tcp_echo_server: 01-basic-tcp-udp/tcp_echo_server.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 01-basic-tcp-udp/tcp_echo_server.c $(COMMON) -o $@

$(BUILD_DIR)/tcp_echo_client: 01-basic-tcp-udp/tcp_echo_client.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 01-basic-tcp-udp/tcp_echo_client.c $(COMMON) -o $@

$(BUILD_DIR)/udp_echo_server: 01-basic-tcp-udp/udp_echo_server.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 01-basic-tcp-udp/udp_echo_server.c $(COMMON) -o $@

$(BUILD_DIR)/udp_echo_client: 01-basic-tcp-udp/udp_echo_client.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) 01-basic-tcp-udp/udp_echo_client.c -o $@

$(BUILD_DIR)/nonblocking_accept_demo: 02-blocking-nonblocking/nonblocking_accept_demo.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 02-blocking-nonblocking/nonblocking_accept_demo.c $(COMMON) -o $@

$(BUILD_DIR)/select_echo_server: 03-select/select_echo_server.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 03-select/select_echo_server.c $(COMMON) -o $@

$(BUILD_DIR)/poll_echo_server: 04-poll/poll_echo_server.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 04-poll/poll_echo_server.c $(COMMON) -o $@

$(BUILD_DIR)/epoll_echo_server: 05-epoll/epoll_echo_server.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 05-epoll/epoll_echo_server.c $(COMMON) -o $@

$(BUILD_DIR)/epoll_buffered_echo_server: 05-epoll/epoll_buffered_echo_server.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 05-epoll/epoll_buffered_echo_server.c $(COMMON) -o $@

$(BUILD_DIR)/length_prefixed_codec_demo: 06-summary-and-pitfalls/length_prefixed_codec_demo.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) 06-summary-and-pitfalls/length_prefixed_codec_demo.c -o $@

$(BUILD_DIR)/thread_per_connection_echo_server: 07-network-models/thread_per_connection_echo_server.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 07-network-models/thread_per_connection_echo_server.c $(COMMON) -pthread -o $@

$(BUILD_DIR)/reactor_threadpool_demo: 07-network-models/reactor_threadpool_demo.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 07-network-models/reactor_threadpool_demo.c $(COMMON) -pthread -o $@

$(BUILD_DIR)/multi_reactor_demo: 07-network-models/multi_reactor_demo.c $(COMMON) common/net_utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) 07-network-models/multi_reactor_demo.c $(COMMON) -pthread -o $@

clean:
	rm -rf $(BUILD_DIR)
