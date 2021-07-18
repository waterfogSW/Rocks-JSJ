# DB 안쓰고 ../uploaded 폴더에 바로 파일 저장

from flask import Flask, render_template, request, jsonify
from pymongo import MongoClient
import os

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = './uploaded'
app.secret_key = "super secret key"


@app.route('/')
def home():
    return render_template('upload.html')

@app.route('/upload', methods=['GET', 'POST'])
def uploader_file():
    if request.method == 'POST':
        file = request.files['file']
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], file.filename))
        return show_video(file.filename)

@app.route('/video')
def show_video(name):
    return render_template('video.html')


if __name__ == '__main__':
    app.debug = False
    app.run()