import serial
import random
import time
import requests
import math
from statistics import mean
from pushsafer import Client
# lets import client from pushsafer
# okay
new_values = []
gsr_threshold = 1000
heart_threshold = 50
ser = serial.Serial('COM6', 9600)
client = Client('KJaaMVZCG8TN3uFrgwO2')
# resp = client.send_message("Hey are you okay?","Consent Message","66952",None, "3","2","https://www.pushsafer.com","Open Pushsafer","0","4","60","None","1","","Yes,No,Maybe")
flag = 0

# read gsr and heart data


def read_sensor(ser):
    # writing command to begin collecting data
    print("hi")

    gsr = []
    bpm = []
    ax = []
    ay = []
    az = []

    for i in range(10):
        new_values = ser.readline().decode('utf-8').strip()
        new_values = new_values.split(' ')
        print(new_values)
        new_values = new_values
        gsr.append(float(new_values[0]))
        bpm.append(float(new_values[1]))
        ax.append(float(new_values[2]))
        ay.append(float(new_values[3]))
        az.append(float(new_values[4]))
        time.sleep(1)

    # print("length")
    # print(len(new_values))

    gsr_value = mean(gsr)
    heart_rate = mean(bpm)
    ax = mean(ax)
    ay = mean(ay)
    az = mean(az)

    return gsr_value, heart_rate, ax, ay, az


# function to process the data and call ifttt
def data_process():
    x = ""
    gsr_value, heart_rate, ax, ay, az = read_sensor(ser)
    global flag
    if gsr_value < gsr_threshold and heart_rate > heart_threshold:

        if ax < 1 and ay < 1 and az < 1:
            # calll ifttt
            print("Calling confirmation")
            # total_avg = sum(gsr_data,heart_data,acc_data,acc_data2)/3
        # if not, the user is probably working out and is there is an increase in HR and GSR
            # status = 400
            # attempts = 0
            # while status >= 400 and attempts <= 5:
            #     req = requests.post(url=MAKER_URL, data=total_avg)
            #     status = req.status_code
            #     attempts += 1
            #     time.sleep(1)

            if flag == 0:
                # resp = client.send_message()
                resp = client.send_message("Hey are you okay?", "Consent Message", "66952", "5", "33", "2",
                                           "https://www.pushsafer.com", "Open Pushsafer", "0", "4", "60", "None", "1", "1", "Yes|No|Maybe", "1")
                flag = 1
                link = "https://www.pushsafer.com/api-m?k=KJaaMVZCG8TN3uFrgwO2&d=66952"
                while x == "":
                    f = requests.get(link).json()
                    message_id = list(f['messages'].keys())[0]
                    x = f['messages'][message_id]['answer']
                if x == "No":
                    resp = client.send_message("Your kid is experiencing a panic attack", "Consent Message", "67146", "None", "20", "3",
                                               "https://www.pushsafer.com", "Open Pushsafer", "0", "4", "60", "None", "1", "None")
                    flag = 0
                    time.sleep(30)
            elif flag == 1:
                # resp = client.send_message("Hey are you okay?", "Consent Message", "66952", "5", "33", "2",
                #    "https://www.pushsafer.com", "Open Pushsafer", "0", "4", "60", "None", "1" ,"1", "Yes|No|Maybe","1")
                resp = client.send_message("Your kid is experiencing a panic attack", "Consent Message", "67146", "None", "20", "3",
                                           "https://www.pushsafer.com", "Open Pushsafer", "0", "4", "60", "None", "1", "None")
                flag = 0
                time.sleep(30)
        else:
            print("Looks like Person is working out")


if __name__ == '__main__':
    while (True):
        data_process()
        time.sleep(5)
