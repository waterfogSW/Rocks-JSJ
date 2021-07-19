# MongoDB에 파일 저장

from flask import Flask, render_template, request, jsonify
from pymongo import MongoClient
import os

app = Flask(__name__)
client = MongoClient('localhost', 27017)
db = client.myDB

app.secret_key = "super secret key"
# app.config['UPLOAD_FOLDER'] = './uploaded'

@app.route('/')
def home():
    return render_template('upload.html')

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        doc = {
            'name': file.filename,
            'contents': file.read()
        }
        db.video.insert_one(doc)
        return show_video(file.filename)

@app.route('/video')
def show_video(name):
    return render_template('video.html')

if __name__ == '__main__':
    app.debug = False
    app.run()