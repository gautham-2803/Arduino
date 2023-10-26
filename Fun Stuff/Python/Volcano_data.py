import serial
import time
import requests

# @brief: Send a read/write command to the Arduino
# @par ser: The serial port instance
# @par command: The name of the read/write command
# @ret None
def send_command(ser, command):
    ser.write(str.encode(command+'\n'))
    time.sleep(2) #need time so don't overrun the serial port when changing the led bar

# @brief: Configure the Serial port
# @par None
# @ret ser: Instantiation of Serial Port
def serial_port():
    ser = serial.Serial(
        port='COM5', 
        baudrate=115200,
        timeout=None)
        #don't forget the port
    print("Connected to: " + ser.portstr)
    return ser

# @brief: Get volcano ID and alert level data
# @par None
# @ret volcano: List of Volcano ID's
# @ret level: List of Volcano Alert levels
def get_volcano_data():
    r = requests.get('https://api.geonet.org.nz/volcano/val') #api link
    data = r.json()
    #print(data)
    feature = data['features']
    #print (feature)
    volcano = []
    level = []
    
    for result in feature:
        properties = result['properties']
        volcano.append(properties['volcanoID'])
        level.append(properties['level'])

    # print (volcano)
    # print(level)
    
    return volcano, level

# Make sure to check and wait for the Acknowledgeent string from the Arduino
def main():
    ser = serial_port()
    
    while(1):
        print("Retrieving latest volcano data")
        volcano, level = get_volcano_data()
        for index in range(0, len(volcano)):
            send_command(ser, "COM_VOLCANO_LEVEL")
            print("Displaying " + volcano[index] + ": " + str(level[index]))
            send_command(ser, str(level[index]))

if __name__ == "__main__":
    main()
