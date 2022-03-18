import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
import threading

# Firestore database object
db = None
# Create an Event for notifying main thread.
callback_done = threading.Event()

def connect():
  print("Connecting to firestore...\t", end="")
  cred = credentials.Certificate("./serviceAccountKey.json")
  firebase_admin.initialize_app(cred, {
    'projectId': 'auhack2022',
  })
  print("✅");
  return firestore.client()

# Create a callback on_snapshot function to capture changes
def on_snapshot(doc_snapshot, changes, read_time):
  for doc in doc_snapshot:
      print(f'Received document snapshot: {doc.id} => {doc.to_dict()}')
  callback_done.set()

def listen(db):
  print("Setting up listener...\t\t", end="")
  doc_ref = db.collection(u'employees')
  doc_watch = doc_ref.on_snapshot(on_snapshot)
  print("✅")
