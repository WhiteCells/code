import json


def split_text_by_json(text):
    """
    输入:
    {"type": "audio", "file": "prompt1.wav", "text": "你好，这里是赫诚律所"}
    {"type": "tts", "text": "受分期乐平台委托，"}
    {"type": "audio", "file": "prompt2.wav", "text": "来调解你违约的事情，"}
    {"type": "tts", "text": "请问是王福建吧？"}
    输出:
    [
        {"type": "audio", "file": "prompt1.wav", "text": "你好，这里是赫诚律所"},
        {"type": "tts", "text": "受分期乐平台委托，"},
        {"type": "audio", "file": "prompt2.wav", "text": "来调解你违约的事情，"},
        {"type": "tts", "text": "请问是王福建吧？"},
    ]
    """
    result = []
    for line_no, line in enumerate(text.splitlines(), 1):
        line = line.strip()
        if not line:
            continue
        obj = json.loads(line)
        if "type" not in obj or "text" not in obj:
            raise ValueError(f"第 {line_no} 行缺少必要字段")
        if obj["type"] == "audio" and "file" not in obj:
            raise ValueError(f"第 {line_no} 行 audio 缺少 file 字段")
        result.append(obj)
    return result


if __name__ == "__main__":
    text = """
{\"type\": \"audio\", \"file\": \"prompt1.wav\", \"text\": \"你好，这里是赫诚律所\"}\n{\"type\": \"tts\", \"text\": \"受分期乐平台委托，\"}\n{\"type\": \"audio\", \"file\": \"prompt2.wav\", \"text\": \"来调解你违约的事情，\"}\n{\"type\": \"tts\", \"text\": \"请问是王福建吧？\"}
    """
    result = split_text_by_json(text)

    for item in result:
        print(item)
        print(item["text"])
