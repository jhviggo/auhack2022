import repository
import ser

print("Application starting...")
db = repository.connect()
repository.listen(db)

conn = ser.connect()
ser.readline(conn)

# Main loop
while True:
  pass