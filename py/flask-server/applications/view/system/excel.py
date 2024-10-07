from applications.common.utils.upload import upload_one_excel
from applications.schemas import ExcelSchema
from applications.common.utils import upload as upload_curd
from applications.common.utils.rights import authorize
from applications.models import Excel
from applications.extensions import db
from applications.common.utils.http import success_api, fail_api, table_api
from flask import Blueprint, request, render_template
from flask_login import current_user


bp = Blueprint('adminExcel', __name__, url_prefix='/excel')


@bp.get('/')
@authorize('system:excel:main')
def index():
    return render_template('system/excel/excel.html')


@bp.get('/table')
@authorize('system:excel:main')
def table():
    csvs = Excel.query.filter(Excel.create_by == current_user.username).order_by(db.desc(Excel.create_time)).layui_paginate()
    data = ExcelSchema(many=True).dump(csvs)
    return table_api(data=data, count=csvs.total)


@bp.get('/upload')
@authorize('system:excel:add')
def upload():
    return render_template('system/excel/excel_add.html')


@bp.post('/upload')
@authorize('system:excel:add')
def upload_api():
    if 'file' in request.files:
        excel = request.files['file']
        mime = request.files['file'].content_type
        return upload_one_excel(excel=excel, mime=mime)
    return fail_api(msg='无文件请求')


@bp.get('/view/<int:id>')
@authorize('system:excel:view')
def view(id):
    return upload_curd.view_excel_by_id(id)


@bp.post('/delete/<int:id>')
@authorize('system:excel:delete')
def delete(id):
    return upload_curd.delete_excel_by_id(id)


@bp.get('/download/<int:id>')
@authorize('system:excel:download')
def download(id):
    return upload_curd.download_excel_by_id(id)


@bp.get('/download/template')
@authorize('system:excel:template')
def template():
    return upload_curd.download_template()


@bp.post('/upload/upload/<int:id>')
@authorize('system:excel:upload')
def api_upload(id):
    return upload_curd.upload_excel_by_id(id)


@bp.post('/api/receive')
def api_receive():
    print('===> api')
    return upload_curd.api_receive_json()