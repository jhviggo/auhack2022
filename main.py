import repository
import ser

print("Application starting...")
ser.connect()

db = repository.connect()
repository.listen(db)

ser.loopSerial()

# Main loop
while True:
  pass