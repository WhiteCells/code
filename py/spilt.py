import re


def split_text(text):
    # """
    # 根据中文和英文标点符号分句
    # """
    # sentences = re.split(r"(?<=[。！？!?,，；;])", text)
    # sentences = [s.strip() for s in sentences if s.strip()]
    # return sentences
    """
    每两小句作为一条记录
    """
    res = []
    sentences = re.split(r"(?<=[。！？!?,，；;])", text)
    print("sentences:", sentences)
    for i in range(0, len(sentences), 2):
        if i + 1 < len(sentences):
            res.append(sentences[i] + sentences[i + 1])
        else:
            res.append(sentences[i])
    return res


if __name__ == "__main__":
    text = "您看能否找到正确的地址或其他联系方式呢？建议您可以先尝试联系收件人的同事、邻居或物业帮忙确认信息。"
    print(split_text(text))