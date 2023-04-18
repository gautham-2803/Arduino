import serial
import random 
import time
import requests 
import math

new_values =[]
gsr_threshold = 500
heart_threshold = 100
ser = serial.Serial('COM5', 9600)

# IFTTT details

EVENT_NAME = "too_bright" 
KEY = "" #enter your maker key 
MAKER_URL = "https://maker.ifttt.com/trigger/{}/json/with/key/{}".format(EVENT_NAME, 
KEY) 

# read gsr and heart data
def read_heart_gsr(ser):
    #writing command to begin collecting data
    print("hi")
    new_values = ser.readline().decode('utf-8').strip()
    new_values = new_values.split(';')
    print("length")
    print(len(new_values))

    gsr_value = new_values[0]
    heart_rate = new_values[1]
    print(gsr_value, heart_rate)

# read accelerometer data
def read_accelerometer():
    ser.write(b'A')
    accelerometer = ser.readline().decode('utf-8').strip()
    return accelerometer

# function to process the data and call ifttt
def data_process():
    gsr_data, heart_data = read_heart_gsr()
    if gsr_data > gsr_threshold and heart_data > heart_threshold:
        acc_data = read_accelerometer()
        # delaying for 30 seconds to check if user has moved or stagnant
        time.delay(30)
        acc_data2 = read_accelerometer()
        # if both data is the same, we can send for confirmation/consent 
        if acc_data == acc_data2:
            # calll ifttt
            print("Calling confirmation")
            total_avg = sum(gsr_data,heart_data,acc_data,acc_data2)/3
        # if not, the user is probably working out and is there is an increase in HR and GSR 
            status = 400 
            attempts = 0 
            while status >= 400 and attempts <= 5: 
                req = requests.post(url=MAKER_URL, data=total_avg) 
                status = req.status_code 
                attempts += 1 
                time.sleep(1)    
        else:
            print("Looks like Person is working out")
            data_process()






if __name__ == '__main__':
    # while(True):
    #     data_process()
    #     time.delay(10)
    read_heart_gsr(ser)
