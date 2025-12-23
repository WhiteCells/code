import json

async def get_history_str_by_agent() -> str:
    history = [
        {'role': 'client', 'text': '请开始话术提醒'},
        {'role': 'server', 'text': '你好，我是hbhc律所的客服，请问有什么可以帮您？'},
        {'role': 'client', 'text': '我想了解一下我的还款计划'},
        {'role': 'client', 'text': '我想了解一下我的还款计划，我钱了多少钱'},
        {'role': 'client', 'text': '我想了解一下我的还款计划，我钱了多少钱，还有多久还清'},
        {'role': 'server', 'text': '你好，关于您的还款计划，您目前的余额是5000元，预计还清时间是6个月。请问还有其他需要帮助的吗？'},
        {'role': 'client', 'text': '我想了解一下我的还款计划，我钱了多少钱，还有多久还清'},
    ]

    filtered = []
    last_client = None

    for h in history:
        if h["role"] == "client":
            last_client = h["text"]
        else:
            if last_client is not None:
                filtered.append({"role": "client", "text": last_client})
                last_client = None

            filtered.append({"role": "server", "text": h["text"]})

    if last_client is not None:
        filtered.append({"role": "client", "text": last_client})

    return json.dumps(filtered, ensure_ascii=False)

def main():
    import asyncio
    result = asyncio.run(get_history_str_by_agent())
    print(result)

if __name__ == "__main__":
    main()