PasswordLineEdit 对象内部添加 QAction：
    - clear_action 实现点击后清除 QLineEdit
    - show_pass_action 实现点击后显示或隐藏密码
    - drop_action 实现点击后显示或隐藏账号下拉菜单

PasswordLineEdit 对象细节：
    - 输入文本居中
    - 点击时才会聚焦
    - 聚焦时才显示 clear_action 与 show_pass_action
    - 点击其他界面取消聚焦