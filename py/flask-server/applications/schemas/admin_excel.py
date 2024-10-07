from applications.extensions import ma
from marshmallow import fields


class ExcelSchema(ma.Schema):
    id = fields.Integer()
    name = fields.Str()
    href = fields.Str()
    mime = fields.Str()
    size = fields.Str()
    repair_status = fields.Str()
    create_time = fields.DateTime()
    create_by = fields.Str()