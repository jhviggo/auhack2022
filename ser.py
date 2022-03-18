import serial
conn = None

def connect():
  print("connecting...", end="")
  conn = None
  try:
    conn = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=3.0)
  except Exception as e:
    print(e)
  print("✅")
  return conn

def readline(conn):
  print("[ OUTPUT ]")
  try:
    while True:
      line_received = conn.readline().decode().strip()
      print("line recieved: " + line_received);
  except Exception as e:
    print(e)

if conn:
  conn.close()