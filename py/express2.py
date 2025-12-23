import json
import requests
from queue import Queue
from threading import Thread
import time
from datetime import datetime

url = 'http://192.168.2.3/v1/chat-messages'
headers1 = {
    'Authorization': 'Bearer app-n1yaLxtJlXP1GI2QTr1tljGJ',
    'Content-Type': 'application/json'
}
conversation_id = ""
current_task_id = ""

def get_timestamp():
    """获取当前时间戳 [小时:分:秒:毫秒]"""
    now = datetime.now()
    return f"[{now.hour:02d}:{now.minute:02d}:{now.second:02d}:{now.microsecond//1000:03d}]"

def get_message(text, header, history, userinformation, queue, record_history=None):
    """
    发送文本给LLM,返回LLM的回答
    :param text: 发送给LLM的文本内容
    :param queue: 用于传递响应的队列
    :param record_history: 记录历史的回调函数
    :return LLM的文本回答
    """
    global conversation_id
    global current_task_id
    start_time = time.time()  # 记录请求开始时间
    data = {
        "inputs": {"userinformation": str(userinformation)},
        "query": str(history)+ "当前回复：{'role': 'client', 'text': "+text+"}",
        "response_mode": "streaming",
        "conversation_id": str(conversation_id),
        "user": "abc-123"
    }
    # 发送POST请求并获取响应
    response = requests.post(url, headers=header, data=json.dumps(data), stream=True)

    if response.status_code != 200:
        print(f"{get_timestamp()} Error: {response.status_code} {response.text}")
        return None, None

    reply = ""
    processing = False  # 是否开始处理数据
    
   # 逐行读取响应内容并实时处理
    for line in response.iter_lines():        
        if line:
            line = line.decode('utf-8')
            if line.startswith('data: '):
                line = line[6:]  # 去掉前缀 'data: '
                try:
                    chunk_data = json.loads(line)
                    #print(f"{get_timestamp()} 接收到数据块: {chunk_data}\n")
                except json.JSONDecodeError:
                    print(f"{get_timestamp()} Failed to decode JSON: {line}")
                    continue

                # 处理不同的事件类型
                if chunk_data.get('event') == 'message':
                    processing = True
                    reply += chunk_data.get('answer', '')
                    queue.put(chunk_data.get('answer'))
                elif chunk_data.get('event') == 'workflow_started':
                    conversation_id = chunk_data.get('conversation_id', conversation_id)
                    current_task_id = chunk_data.get('task_id', current_task_id)
                elif chunk_data.get('event') == 'message_end':
                    processing = False
                elif chunk_data.get('event') == 'workflow_finished' and processing:
                    end_time = time.time()  # 记录请求结束时间
                    elapsed_time = end_time - start_time
                    print(f"{get_timestamp()} 请求正常完成，运行时间: {elapsed_time:.2f}秒")
                    processing = False
                    #print(f"{get_timestamp()} 跳出循环1。")
    

    #print(f"{get_timestamp()} 跳出循环2。")


   # 将完整回复和元数据传递给回调函数
    if record_history:
        record_history(history, text, reply)

    # 标志任务结束
    queue.put(None)
    return reply

# 记录对话历史
def record_history(history, text, reply):
    """
    记录对话历史
    :param text: 用户输入的文本
    :param reply: LLM的回答
    """
    history.append({"role": "client", "text": text})
    history.append({"role": "server", "text": reply})
    return history


# 实时打印函数
def streaming_print(queue):
    """
    从队列中读取数据并实时打印
    :param queue: 包含中间结果的队列
    """
    while True:
        chunk = queue.get()
        if chunk is None:
            break
        print(chunk, end='', flush=True)
    print("\n")  # 打印完成后换行


# 停止当前任务
def cancel_current_task():
    """
    使用current_task_id停止当前任务
    """
    global current_task_id

    # 根据提供的task_id停止任务
    stop_url = f"http://192.168.2.3/v1/chat-messages/{current_task_id}/stop"
    stop_data = {
        "user": "abc-123"
    }
    try:
        response = requests.post(stop_url, headers=headers1, data=json.dumps(stop_data))
        if response.status_code == 200:
            print(f"{get_timestamp()} 任务 {current_task_id} 已停止")
        else:
            print(f"{get_timestamp()} 停止任务 {current_task_id} 失败，状态码: {response.status_code}")
    except Exception as e:
        print(f"{get_timestamp()} 停止任务时发生错误: {str(e)}")

if __name__ == '__main__':
    # step 1: 用户信息
    history = []
    userinformation = "姓名:王福建;性别:男;身份证:350124199012022***;逾期金额:3155.81;逾期天数:2057;最低减免:3100;资金方全称:分期乐;委案结束日期:2025-12-31" 
    print(f"{get_timestamp()} 用户信息如下： {userinformation}", end='\n', flush=True)

    # step 2: 获取用户信息完成后，开始对话
    queue = Queue()
    client_text = "开场话术"

    # 启动对话的线程
    thread = Thread(target=get_message, args=(client_text, headers1, history, userinformation, queue, record_history))
    thread.daemon = True
    thread.start()

    print(f"{get_timestamp()} 即将开始调解:")
    print("LLM:", end='', flush=True)
    print_thread = Thread(target=streaming_print, args=(queue,))
    print_thread.start()

    thread.join()
    print_thread.join()

    # step 3: 使用字符串数组，每隔2秒输入一次，并测试打断功能
    inputs = [
        "你好，我邮政快递的",
        "对啊", 
        "你们的包裹联系不上收件人，电话打不通", 
        "12",
        "34",
        "56",
        "789",
        "12",
        "34",
        "对的",
        "找不到",
        "你说什么",
        "都没有",
        "可以详细解释下吗",
        "已经投了3次",
    ]

    # 用于存储请求线程的列表
    active_threads = []

    for i, client_text in enumerate(inputs):
        print(f"{get_timestamp()} USER: {client_text}")
        
        # 如果当前有活跃的请求，尝试打断它
        if active_threads and current_task_id:
            # 停止当前任务
            cancel_current_task()
            for t in active_threads:
                t.join(timeout=0.2)  # 最多等待0.2秒
            active_threads.clear()

        queue = Queue()
        start_time = time.time()  # 记录请求开始时间
        thread = Thread(target=get_message, args=(client_text, headers1, history, userinformation, queue, record_history))
        thread.daemon = True
        thread.start()
        active_threads.append(thread)

        print("\nLLM:", end='', flush=True)
        print_thread = Thread(target=streaming_print, args=(queue,))
        print_thread.start()
        # print_thread.join()  # 等待输出完成

        # 等待2秒后开始下一个请求（即使当前请求未完成）
        time.sleep(1.2)

        print_thread.join(timeout=0.1)  # 等待输出完成，但不阻塞太长时间
        end_time = time.time()  # 记录请求开始后的时间（即2秒后）
        elapsed_time = end_time - start_time
        print(f"{get_timestamp()} 当前请求已运行: {elapsed_time:.2f}秒")

    # 等待所有线程结束
    for t in active_threads:
        t.join()

    # 打印对话历史
    print(f"{get_timestamp()} 通话结束，本次通话的对话历史如下：")
    for entry in history:
        if entry["role"] == "client":
            print(f"{get_timestamp()} USER: {entry['text']}")
        else:
            print(f"{get_timestamp()} LLM: {entry['text']}")
    print("=============================================\n")
        