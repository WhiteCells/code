import logging
import os
from datetime import timedelta


# from urllib.parse import quote_plus as urlquote

# 地址修复状态
REPAIR_STATUS = {
    'unrepaired': '0',
    'repairing': '1',
    'repaired': '2'
}

# id 前缀
ID_PREFIX = 'flask_server_'

# 调用 api 的 json 数据
payload = {
    'entity_no': 0,  # 客户
    'entrust_id': "",  # 委托方Id  # 必填
    'task_id': '',  # 任务Id  # 必填
    'begin_time': "委案开始时间",
    'returnUrl': "http://www.jhqtj.com:8088/hcls0/customerTask/returnAddressData",  # 数据返回的平台地址接口  # 必填
    'customer_info': [
        {
            'customer_id': "客户号",  # 必填
            'homeAddress': "家庭地址",  # 必填
            'beginTime': "委案开始时间",  # 必填
            'liveAddress': "居住地址",  # 必填
            'user_identification': "身份证",  # 必填
            'address1': "其他地址1",  # 未修复可不传值
            'address2': "其他地址2",  # 未修复可不传值
        }
    ]
}

class BaseConfig:
    SUPERADMIN = 'admin'

    SYSTEM_NAME = 'Pear Admin22'
    # 主题面板的链接列表配置
    SYSTEM_PANEL_LINKS = [
        {
            "icon": "layui-icon layui-icon-auz",
            "title": "官方网站",
            "href": "http://www.pearadmin.com"
        },
        {
            "icon": "layui-icon layui-icon-auz",
            "title": "开发文档",
            "href": "http://www.pearadmin.com"
        },
        {
            "icon": "layui-icon layui-icon-auz",
            "title": "开源地址",
            "href": "https://gitee.com/Jmysy/Pear-Admin-Layui"
        }
    ]

    UPLOADED_PHOTOS_DEST = 'static/upload'
    UPLOADED_FILES_ALLOW = ['gif', 'jpg']
    UPLOADS_AUTOSERVE = True

    UPLOADED_EXCELS_DEST = 'static/upload'
    UPLOADED_EXCELS_ALLOW = ['csv', 'xls', 'xlsx']
    RESULT_EXCELS_DEST = 'static/upload/result'

    TEMPLATE_EXCELS_DEST = 'static/upload/template/template.xlsx'
    RESULT_TEMPLATE_EXCELS_DEST = 'static/upload/template/result_template.xlsx'

    # 上传的数据修复地址
    REPAIR_API_URL = 'http://192.168.10.125:8081/address'
    # 回调至服务器地址
    RETURN_URL = 'http://192.168.3.233:8000/api/receive'

    # JSON配置
    JSON_AS_ASCII = False

    SECRET_KEY = "pear-system-flask"

    # mysql 配置
    # MYSQL_USERNAME = "root"
    # MYSQL_PASSWORD = "123456"
    # MYSQL_HOST = "127.0.0.1"
    # MYSQL_PORT = 3306
    # MYSQL_DATABASE = "PearAdminFlask"

    # 数据库的配置信息
    # SQLALCHEMY_DATABASE_URI = 'sqlite:///../pear.db'
    # SQLALCHEMY_DATABASE_URI = f"mysql+pymysql://{MYSQL_USERNAME}:{urlquote(MYSQL_PASSWORD)}@{MYSQL_HOST}:{MYSQL_PORT}/{MYSQL_DATABASE}?charset=utf8mb4"
    # SQLALCHEMY_DATABASE_URI = f"mysql+pymysql://root:10101@localhost:3306/PearAdmin?charset=utf8mb4"
    SQLALCHEMY_DATABASE_URI = f"mysql+pymysql://root:3215@localhost:3306/PearAdmin?charset=utf8mb4"

    # 默认日志等级
    LOG_LEVEL = logging.WARN
    """
    flask-mail配置
    """
    MAIL_SERVER = 'smtp.qq.com'
    MAIL_USE_TLS = False
    MAIL_USE_SSL = True
    MAIL_PORT = 465
    MAIL_USERNAME = '123@qq.com'
    MAIL_PASSWORD = 'XXXXX'  # 生成的授权码
    MAIL_DEFAULT_SENDER = MAIL_USERNAME

    # 插件配置，填写插件的文件名名称，默认不启用插件。
    PLUGIN_ENABLE_FOLDERS = []

    # 配置多个数据库连接的连接串写法示例
    # HOSTNAME: 指数据库的IP地址、USERNAME：指数据库登录的用户名、PASSWORD：指数据库登录密码、PORT：指数据库开放的端口、DATABASE：指需要连接的数据库名称
    # MSSQL:    f"mssql+pymssql://{USERNAME}:{PASSWORD}@{HOSTNAME}:{PORT}/{DATABASE}?charset=cp936"
    # MySQL:    f"mysql+pymysql://{USERNAME}:{PASSWORD}@{HOSTNAME}:{PORT}/{DATABASE}?charset=utf8mb4"
    # Oracle:   f"oracle+cx_oracle://{USERNAME}:{PASSWORD}@{HOSTNAME}:{PORT}/{DATABASE}"
    # SQLite    "sqlite:/// database.db"
    # Postgres f"postgresql+psycopg2://{USERNAME}:{PASSWORD}@{HOSTNAME}:{PORT}/{DATABASE}"
    # Oracle的第二种连接方式
    # dsnStr = cx_Oracle.makedsn({HOSTNAME}, 1521, service_name='orcl')
    # connect_str = "oracle://%s:%s@%s" % ('{USERNAME}', ' {PASSWORD}', dsnStr)

    #  在SQLALCHEMY_BINDS 中设置：'{数据库连接别名}': '{连接串}'
    # 最后在models的数据模型class中，在__tablename__前设置        __bind_key__ = '{数据库连接别名}'  即可，表示该数据模型不使用默认的数据库连接，改用“SQLALCHEMY_BINDS”中设置的其他数据库连接
    #  SQLALCHEMY_BINDS = {
    #    'testMySQL': 'mysql+pymysql://test:123456@192.168.1.1:3306/test?charset=utf8',
    #    'testMsSQL': 'mssql+pymssql://test:123456@192.168.1.1:1433/test?charset=cp936',
    #    'testOracle': 'oracle+cx_oracle://test:123456@192.168.1.1:1521/test',
    #    'testSQLite': 'sqlite:///database.db
    # }
    """
    session
    """

    PERMANENT_SESSION_LIFETIME = timedelta(days=7)

    SESSION_TYPE = "filesystem" # 默认使用文件系统来保存会话
    SESSION_PERMANENT = False  # 会话是否持久化
    SESSION_USE_SIGNER = True  # 是否对发送到浏览器上 session 的 cookie 值进行加密

