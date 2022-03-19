import serial
import time

conn = None
sendData = []

def connect():
  print("connecting...\t\t\t", end="")
  global conn
  try:
    conn = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=3.0)
  except Exception as e:
    print(e)
  print("✅")
  return conn

def loopSerial():
  global sendData
  print("[ OUTPUT ]")
  try:
    while True:
      line_received = conn.readline().decode().strip()
      if line_received:
        print("line recieved: " + line_received);
      if len(sendData) != 0:
        for i in sendData:
          conn.write(i.encode())
          print("line sent: " + i)
        sendData = []
  except Exception as e:
    print(e)

def writeline(line):
  global sendData
  sendData.append(line)

if conn:
  conn.close()