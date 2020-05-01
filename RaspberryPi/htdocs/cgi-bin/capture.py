#!/home/pi/picamera-with-esp32button/RaspberryPi/venv/bin/python

from time import sleep
from picamera import PiCamera
import requests

import cgitb
cgitb.enable()

htdocs_dir = '/home/pi/picamera-with-esp32button/RaspberryPi/htdocs/'
jpeg_name = 'out.jpg'

filename = htdocs_dir + jpeg_name

def capture(filename):
  camera = PiCamera()
  camera.resolution = (1024, 768)
  sleep(2)

  camera.capture(filename)

def notify(filename):
  fileDataBinary = open(filename, 'rb').read()

  line_url = 'https://notify-api.line.me/api/notify'
  header = {'Authorization': 'Bearer er2tC0kLfOchJgh1OiwKupuzZmY4XxRhbOyusvn05Ab'}
  data = dict(message='capture')
  files = {'imageFile': (filename, fileDataBinary, 'image/jpeg')}

  requests.post(line_url, headers=header, data=data, files=files)

def print_response():
  response = '''
  Content-Type: text/html
  
  <html><body>success</body></html>
  '''
  print(response)

if __name__ == "__main__":
  capture(filename)
  notify(filename)
  print_response()

