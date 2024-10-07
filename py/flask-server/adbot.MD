
```shell
flask db init
flask db migrate
flask db upgrade
flask admin init

flask --app app.py run -h 0.0.0.0 -p 8000 --debug
```

```shell
pip install -r requirements.txt
```

```shell
https://pypi.tuna.tsinghua.edu.cn/simple
```

## 应用结构

```应用结构
Pear Admin Flask
├─applications  # 应用
│  ├─extensions  # 注册插件
│  ├─models  # 数据模型
│  ├─static  # 静态资源文件
│  ├─templates  # 静态模板文件
│  └─views  # 视图部分
│     ├─admin  # 后台管理视图模块
│     └─index  # 前台视图模块
├─docs  # 文档说明
├─migrations  # 迁移文件记录
├─requirement  # 依赖文件
└─.env # 项目的配置文件
```

## 资源结构

```资源结构
Pear Admin Flask
├─static    # 项目设定的 Flask 资源文件夹
│  ├─admin    # pear admin flask 的后端资源文件（与 pear admin layui 同步）
│  ├─index    # pear admin flask 的前端资源文件
│  └─upload     # 用户上传保存目录
└─templates # 项目设定的 Flask 模板文件夹
  ├─admin   # pear admin flask 的后端管理页面模板
  │  ├─admin_log    # 日志页面
  │  ├─common       # 基本模板页面（头部模板与页脚模板）
  │  ├─console      # 系统监控页面模板
  │  ├─dept         # 部门管理页面模板
  │  ├─dict         # 数据自动页面模板
  │  ├─mail         # 邮件管理页面模板
  │  ├─photo        # 图片上传页面模板
  │  ├─power        # 权限（菜单）管理页面模板
  │  ├─role         # 角色管理页面模板
  │  ├─task         # 任务设置页面模板
  │  └─user         # 用户管理页面模板
  ├─errors  # 错误页面模板
  └─index   # 主页模板
```

## 修改配置

> **💡提示** 配置文件位于  `applications/config.py` ，打开配置文件看到的是位于 `BaseConfig` 类下的默认配置文件，您可以编写自己的配置类并继承 `BaseConfig` 类。
项目启动时，会调用 `applications/__init__.py` ，这个文件中加载了程序的配置，所以在您编写了自己的类后不要忘记在文件 `applications/__init__.py` 中修改使用的配置类。

> **⚠️注意** 配置文件中对于数据库的配置有所更改，请查看代码中的注释修改配置。

```python
# 部分配置信息如下所示

# 验证密钥（⚠️ 一定要记得修改 ⚠️）
SECRET_KEY = "pear-system-flask"

# 数据库的配置信息
SQLALCHEMY_DATABASE_URI = 'sqlite:///../pear.db'

# 默认日志等级
LOG_LEVEL = logging.WARN

# flask-mail配置
MAIL_SERVER = 'smtp.qq.com'
MAIL_USE_TLS = False
MAIL_USE_SSL = True
MAIL_PORT = 465
MAIL_USERNAME = '123@qq.com'
MAIL_PASSWORD = 'XXXXX'  # 生成的授权码
MAIL_DEFAULT_SENDER = MAIL_USERNAME
```


## 直接安装项目

```bash
pip install -r requirements.txt
```

# 运行项目

+ 一般情况运行项目

```bash
# 初始化数据库
flask db init
flask db migrate
flask db upgrade
flask admin init

# 运行项目
flask --app app.py run -h 0.0.0.0 -p 8000 --debug

# 或者直接调用 app.py
python app.py
```

+ 使用 docker-compose 运行项目

```bash
git clone https://gitee.com/pear-admin/pear-admin-flask

# 安装 docker-compose 
curl -L https://github.com/docker/compose/releases/download/1.26.2/docker-compose-`uname -s`-`uname -m` > /usr/local/bin/docker-compose
chmod +x /usr/local/bin/docker-compose
ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose 

# 运行如下命令，有输出版本，表示 docker-compose 可以用了
docker-compose --version 

# 在当前目录执行如下命令即可以运行 app
docker-compose -f dockercompose.yaml up

# 看到如下表示运行成功，由于 pip 下载慢，需要一些时间，请耐心等待；如果安装失败，重新执行上面的命令即可。

# 运行后在浏览器访问 127.0.0.1:5000 

#如果要停止容器运行，在当前文件夹执行如下命令：
docker-compose -f dockercompose.yaml down
```


默认用户为 `admin` ，密码默认为 `123456` 。