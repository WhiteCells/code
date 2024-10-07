from flask import Flask
from flask_uploads import configure_uploads, UploadSet, IMAGES, DOCUMENTS, DATA

photos = UploadSet('photos', IMAGES)

excels = UploadSet('excels', DOCUMENTS + DATA)

def init_upload(app: Flask):
    configure_uploads(app, photos)
    configure_uploads(app, excels)
