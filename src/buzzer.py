import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

buzzerPin = 22
GPIO.setup(buzzerPin, GPIO.OUT)

while True:
    GPIO.output(buzzerPin, GPIO.HIGH)
    time.sleep(1)
    GPIO.output(buzzerPin, GPIO.LOW)
    time.sleep(1)
