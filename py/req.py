import requests
import json

url = "http://192.168.2.3/v1/chat-messages"

headers = {
    "Authorization": "Bearer app-5wlJJ0WDoyKpZ6t460pb4H3m",
    "Content-Type": "application/json",
}

data = {
    "inputs": {
        "userinformation": "姓名:王福建;性别:男;身份证:350124199012022***;逾期金额:3155.81;逾期天数:2057;最低减免:3100;资金方全称:分期乐;委案结束日期:2025-12-31"
    },
    "query": "[{'role': 'client', 'text': ''}, {'role': 'server', 'text': '你好，这里是湖北赫诚律师事务所，请问你是王福建吧？'}]当前回复：{'role': 'client', 'text': 对，是我}",
    "response_mode": "streaming",
    "conversation_id": "",
    "user": "abc-123",
}

response = requests.post(url, headers=headers, data=json.dumps(data), stream=True)

for line in response.iter_lines():
    if line:
        line = line.decode("utf-8")
        print(line)
        if line.startswith("data: "):
            chunk_data = json.loads(line[6:])
            if chunk_data.get("event") == "message":
                print(chunk_data.get("answer"))
