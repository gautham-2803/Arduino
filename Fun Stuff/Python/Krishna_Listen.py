import datetime
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

cred = credentials.Certificate("krishna722-776b9-firebase-adminsdk-h1hia-3402f4b9de.json")

firebase_admin.initialize_app(cred)



ref = db.reference(path ="/new_devices", url="https://krishna722-776b9-default-rtdb.firebaseio.com")

def dbListen(event): 
    print('Firebase event detected: ') 
    print('Path: ' + event.path) 
    print('Data: ' + str(event.data)) 
    print('Event type: ' + event.event_type) 
 
    now = datetime.datetime.now() 
    human_timestamp = '{y}-{mon}-{d} {h}:{min}:{s}'.format( 
        y=now.year, 
        mon=now.month, 
        d=now.day, 
        h=now.hour, 
        min=now.minute, 
        s=now.second 
    ) 
 
    print(human_timestamp) 
 
import threading 
if __name__ == "__main__": 
    listener = ref.child('devices').listen(dbListen)