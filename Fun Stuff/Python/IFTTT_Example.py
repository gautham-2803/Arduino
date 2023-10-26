import time 
import requests 
import math 
import random 
import serial
import time


ser = serial.Serial('COM5', 9600)

EVENT_NAME = "too_bright" 
KEY = "d23A6rhN16sxMd_kIk0603" #enter your maker key 
MAKER_URL = "https://maker.ifttt.com/trigger/{}/json/with/key/{}".format(EVENT_NAME, 
KEY) 
 
# TOKEN = "BBFF-vH12v5czPluhdrD23cD6icFSUtH8uN"  # Put your TOKEN here 
# DEVICE_LABEL = "Krishna_Arduino"  # Put your device API Label here  
# VARIABLE_LABEL_1 = "light"  # Put your first variable label here 


 
 
def build_payload(): 
    value = ser.readline().decode('utf-8').strip()
    # # Creates two random values for sending data 
    print(value)
    # value_1 = random.randint(-10, 50) 
    if int(value) > 400 :
        print("The light value is too bright :" + str(value) + ". The web hook is being called")
        
        post_request(value)
    else:
        print("The light value is okay and no webhook will be invoked")
        

 
def post_request(payload): 
    # # Creates the headers for the HTTP requests 
    # url = "https://maker.ifttt.com/use/" 
    # url = "{}/api/v1.6/devices/{}".format(url, DEVICE_LABEL) 
    # headers = {"X-Auth-Token": TOKEN, "Content-Type": "application/json"} 
 
    # Makes the HTTP requests 
    status = 400 
    attempts = 0 
    while status >= 400 and attempts <= 5: 
        req = requests.post(url=MAKER_URL, data=payload) 
        status = req.status_code 
        attempts += 1 
        time.sleep(1) 
 
    # Processes results 
    print(req.status_code, req.text) 
    if status >= 400: 
        print("[ERROR] Could not send data after 5 attempts, please check youur token credentials and internet connection") 
        return False 
 
    print("[INFO] request made properly, your device is updated") 
    return True 
 
 
if __name__ == '__main__': 
    while (True): 
        build_payload()
        time.sleep(30) 
        print("printing after 30 seconds")