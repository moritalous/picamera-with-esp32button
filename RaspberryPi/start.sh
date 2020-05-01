#!/bin/sh

cd htdocs

/home/pi/picamera-with-esp32button/RaspberryPi/venv/bin/python -m http.server --cgi
