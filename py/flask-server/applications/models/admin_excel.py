import datetime
from applications.extensions import db


class Excel(db.Model):
    __tablename__ = 'admin_excel'
    id = db.Column(db.Integer, primary_key=True, comment='id')
    name = db.Column(db.String(255), comment='文件名')
    href = db.Column(db.String(255), comment='链接')
    mime = db.Column(db.CHAR(255), comment='类型')
    size = db.Column(db.CHAR(50), comment='大小')
    repair_status = db.Column(db.CHAR(1), comment='修复状态')
    create_time = db.Column(db.DateTime, default=datetime.datetime.now, comment='创建时间')
    create_by = db.Column(db.String(255), comment='创建者')