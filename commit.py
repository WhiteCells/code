import requests

GITLAB_URL = "http://192.168.2.253/api/v4"
TOKEN = "AwtSHGQktMFyxSGENxKY"
HEADERS = {"PRIVATE-TOKEN": TOKEN}

SINCE = "2026-01-01T00:00:00Z"
UNTIL = "2026-03-31T23:59:59Z"
AUTHOR = "xuan2692659908@foxmail.com"

def get_projects():
    projects = []
    page = 1

    while True:
        url = f"{GITLAB_URL}/projects"
        params = {
            "membership": True,
            "per_page": 100,
            "page": page
        }
        res = requests.get(url, headers=HEADERS, params=params)
        data = res.json()

        if not data:
            break

        projects.extend(data)
        page += 1

    return projects


def get_commits(project_id):
    commits = []
    page = 1

    while True:
        url = f"{GITLAB_URL}/projects/{project_id}/repository/commits"
        params = {
            "since": SINCE,
            "until": UNTIL,
            "author": AUTHOR,
            "per_page": 100,
            "page": page
        }

        res = requests.get(url, headers=HEADERS, params=params)
        data = res.json()

        if not data:
            break

        commits.extend(data)
        page += 1

    return commits


def main():
    all_commits = []

    projects = get_projects()

    for p in projects:
        project_id = p["id"]
        project_name = p["name"]

        commits = get_commits(project_id)

        for c in commits:
            all_commits.append({
                "project": project_name,
                "message": c["title"],
                "date": c["created_at"]
            })

    return all_commits


if __name__ == "__main__":
    commits = main()
    for c in commits:
        print(c)