import serial
import random 
import time
import requests 
import math
#lets import client from pushsafer
# okay 
new_values =[]
gsr_threshold = 250
heart_threshold = 100
ser = serial.Serial('COM3', 9600)

# IFTTT details

EVENT_NAME = "too_bright" 
KEY = "" #enter your maker key 
MAKER_URL = "https://maker.ifttt.com/trigger/{}/json/with/key/{}".format(EVENT_NAME, 
KEY) 

# read gsr and heart data
def read_sensor(ser):
    #writing command to begin collecting data
    print("hi")

    gsr = []
    bpm = []
    ax = []
    ay = []
    az = []

    for i in range(10):
        new_values = ser.readline().decode('utf-8').strip()
        new_values = new_values.split(' ')
        gsr.append(new_values[0])
        bpm.append(new_values[1])
        ax.append(new_values[2])
        ay.append(new_values[3])
        az.append(new_values[4])
        time.sleep(1)

    print("length")
    print(len(new_values))

    gsr_value = math.mean(gsr)
    heart_rate = math.mean(bpm)
    ax = math.mean(ax)
    ay = math.mean(ay)
    az = math.mean(az)

    return gsr_value, heart_rate, ax, ay, az

# read accelerometer data
def read_accelerometer():
    ser.write(b'A')
    accelerometer = ser.readline().decode('utf-8').strip()
    return accelerometer

# function to process the data and call ifttt
def data_process():
    gsr_value, heart_rate, ax, ay, az = read_sensor()
    if gsr_value < gsr_threshold and heart_rate > heart_threshold:
        # acc_data = read_accelerometer()
        # delaying for 30 seconds to check if user has moved or stagnant
        # time.delay(30)
        # acc_data2 = read_accelerometer()
        # if both data is the same, we can send for confirmation/consent 
        if ax > 1.5 or  ay > 1.5 or  az > 1.5  :
            # calll ifttt
            print("Calling confirmation")
            # total_avg = sum(gsr_data,heart_data,acc_data,acc_data2)/3
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
    while(True):
    #     data_process()
    #     time.delay(10)
        read_sensor(ser)
