
import time
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import serial
# ser = serial.Serial('COM5', 9600)
import random



cred = credentials.Certificate("krishna722-776b9-firebase-adminsdk-h1hia-3402f4b9de.json")

firebase_admin.initialize_app(cred)


ref = db.reference(path ="/new_devices", url="https://krishna722-776b9-default-rtdb.firebaseio.com")

def read_data(): # reading data from serial port 
    # value = ser.readline().decode('utf-8').strip()
    value = random.randint(0,999)
    print("Light value is: "+ str(value))
    return value

def devices_update(length):
    count = length

    devices = ref.get("new_devices")
    print("Device list is ")
    print(devices) 

    value = read_data()         
    # assigning random devive name and passing value    
    # data = {"device":"Device " + str(random.randint(0,999)),"light": value, "time": time.time()} 
    data = {"device":"Device " + str(count),"light": value, "time": time.time()} 
    ref.child("new_devices").push().set(data)
    print("New device created")
       

if __name__ == "__main__":
        devices = ref.get("new_devices")
        length = int(len(devices))
        print(length)
        while(True):
            devices_update(length)
            length = length + 1
            time.sleep(30)
            print("printing after 30 seconds")
