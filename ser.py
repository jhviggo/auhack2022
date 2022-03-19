import serial
import time
conn = None
sendData = None

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
      print("line recieved: " + line_received);
      if sendData != None:
        conn.write(sendData.encode())
        print("line sent: " + sendData)
        sendData = None
  except Exception as e:
    print(e)

def writeline(line):
  global sendData
  sendData = line

if conn:
  conn.close()