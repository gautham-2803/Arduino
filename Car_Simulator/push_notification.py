import serial
# import random
import time
import requests
# import math
# from statistics import mean
from pushsafer import Client

ser = serial.Serial('COM11', 115200)
client = Client('79MS9V6QUE0Ti0eu8faN')


def remoteStart():
    x= ""
    resp = client.send_message("Wanna Start your car?", "Remote Start", "75305", "5", "33", "2",
                                            "https://www.pushsafer.com", "Open Pushsafer", "0", "4", "60", "None", "1", "1", "Yes|No", "1")
    
    link = "https://www.pushsafer.com/api-m?k=79MS9V6QUE0Ti0eu8faN&d=75305"
    time.sleep(10)
    while x == "":
        f = requests.get(link).json()
        message_id = list(f['messages'].keys())[0]
        x = f['messages'][message_id]['answer']
        print(x)
    
    if x=="Yes":
        ser.write(b'G')
        print(x)
        print("\n")
        print("Resetting") 
        x=""
    else:
        print("You've chosen not to restart your car this time \n")
        remoteStart()
        


if __name__ =='__main__':
    remoteStart()
    