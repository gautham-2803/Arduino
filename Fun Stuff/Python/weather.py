import serial
import time
import requests
import math

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
# @par url_path
# @ret weather data

def get_weather_data(url):
    api_base = 'https://api.weather.gov/'
    r = requests.get(api_base+url) #api link
    
    data = r.json()
    return data

# @brief : Get Station data
# @par url_path
# @ret station data

def get_station_data(url):
    r = requests.get(url)
    data = r.json()
    stations = data['observationStations']
    for station in stations:
        if station.endswith("KROC"):
            return station
    
    return ""

# @brief : Get Office data from the station
# @par station
# @ret observation stations, cwa, forecast url

def get_office_data(data):
    properties = data['properties']
    cwa = properties['cwa']
    forecastUrl = properties['forecast']
    observationStations = properties['observationStations']

    return cwa, forecastUrl, observationStations

# @brief : Get forecast data
# @par station
# @ret timestamp, temp, relative humidity, windspeed 

def get_forecast(station):

    #https://api.weather.gov/stations/KROC/observations

    r = requests.get(station+"/observations")
    data = r.json()
    forecast = data['features'][0]['properties']
    # getting timestamp
    if 'timestamp' in forecast:
        timestamp = forecast['timestamp']
    else:
        timestamp = None
    
    # getting temperature
    if 'temperature' in forecast:
        if 'value' in forecast['temperature']:
            temperature = forecast['temperature']['value']
        else:
             temperature = None
    else:
        temperature = None
    
    # getting relative humidity 
    if 'relativeHumidity' in forecast:
        if 'value' in forecast['relativeHumidity']:
            relativeHumidity = forecast['relativeHumidity']['value']
        else:
             relativeHumidity = None
    else:
        relativeHumidity = None

    # getting windspeed 

    if 'windSpeed' in forecast:
        if 'value' in forecast['windSpeed']:
            windSpeed = forecast['windSpeed']['value']
        else:
             windSpeed = None
    else:
        windSpeed = None

    return timestamp, temperature, relativeHumidity, windSpeed


# main function

def main():
    ser = serial_port()
    send_command(ser,"90")

    lat = "43.0845"
    long = "-77.6749"
    degree_sign = u'\N{DEGREE SIGN}'

    print("Student Name : Gautham Krishna")
    print("lat: "+ lat+degree_sign+", "+"long: "+long+degree_sign)

    print("Retrieving office data")
    offices= get_weather_data("points/"+lat+"%2c"+long)
    cwa, forecastUrl, observationStations = get_office_data(offices)
    print("\n Forecast Office: "+cwa)

    # station data ID 
    stationID = get_station_data(observationStations)

    # hard coding KROC
    print("\n Observation Station: KROC")

    while(1):
        timestamp, temperature, relativeHumidity, windSpeed = get_forecast(stationID)
        if timestamp is not None:
            print("Timestamp: "+ timestamp)
        if temperature is not None:
            tempF = 1.8*temperature + 32
            tempStr = "Temperature: %.2f" %temperature + degree_sign +\
            "C | %.2f" % tempF + degree_sign+"F"
            print(tempStr)
        if relativeHumidity is not None:
            print("RH: %.2f " %relativeHumidity+"%")
        if windSpeed is not None:
            windMph = windSpeed * 0.621371922
            windStr = "WindSpeed : %.2f" % windSpeed+"km/h"+" | %.2f" %windMph+"mph"
            print(windStr)
    
        severity = 0 # 1-4 for windchill, 5-8 for heat index
        servoAngles =[90, 101.25, 123.75, 146.25, 168.75, 78.75, 56.25, 33.75, 11.25]
        serverityStr = ["Normal", "Cold", "Very Cold", "Danger", "Great Danger"," Caution", \
                        "Extreme Caution", "Danger", "Extreme Danger"]

        if temperature is not None and windSpeed is not None and relativeHumidity is not None:
            # calculate wind cho;;
            if tempF < 50 and windMph > 3:
                windChill = 35.74+(0.6215*tempF) - (35.75*windMph**0.16) + \
                (0.4275*tempF*windMph**0.16)
                windChillC = (windChill - 32) * 0.5556
                print("WindChill : %.2f" %windChillC + degree_sign+"C | %.2f" %windChill +\
                       degree_sign + "F")
                
                # determine severity 

                if windChillC > -25 and windChillC <=50:
                    severity = 1
                elif windChillC > -35 and windChillC <= -25:
                    severity =2
                elif windChillC > -65 and windChillC <= -35:
                    severity =3
                elif windChillC < -60:
                    severity =4
                else:
                    severity =0
            else :
                # calculate heat index 
                # stead man first

                steadman = 0.5*(tempF + 61.0 + ((tempF-68.0)*1.2) + (relativeHumidity*0.094))
                steadmanC = ( steadman - 32 ) * 0.5556

                print("Steadman HI : %.2f" %steadmanC + degree_sign + "C| %.2f" %steadman + \
                       degree_sign + "F")

                avg = (steadman + tempF) /2
                if avg >= 80:
                    HI = -42.379 + 2.04901523 *tempF + 10.14333127 * relativeHumidity - \
                            (.22475541*tempF*relativeHumidity) - (.00683783 * tempF*tempF) - \
                            (.05481717*relativeHumidity*relativeHumidity) + \
                            (.00122874*tempF*tempF*relativeHumidity) + \
                            (.00085282*tempF*relativeHumidity*relativeHumidity) -\
                            (.00000199*tempF*tempF*relativeHumidity*relativeHumidity)
                    
                    if relativeHumidity < 13.00 and (tempF >80 and tempF <112) :
                        ADJUSTMENT =  ((13-relativeHumidity)/4)*math.sqrt((17-abs(tempF-95))/17)
                        HI = HI - ADJUSTMENT
                    elif relativeHumidity > 85.00 and (tempF > 80 and tempF <87):
                        ADJUSTMENT = ((relativeHumidity-85)/10) * ((87-temperature)/5)
                        HI = HI + ADJUSTMENT
                    
                    HIC = (HI -32)*0.5556
                    print("Heat Index :%.2f" %HIC + degree_sign + "C| %.2f" %HI + \
                       degree_sign + "F") 
                    
                    # determine severity on HIC

                    if HIC >=26 and HIC <32:
                        severity =1 
                    if HIC >=32 and HIC <41:
                        severity = 2
                    if HIC >=41 and HIC <54:
                        severity =3
                    if HIC >=54:
                        severity =4
                    else:
                        severity =0
                
                else:
                    # determine severity based on Steadman
                    if steadmanC >=26 and steadmanC <32:
                        severity =1 
                    if steadmanC >=32 and steadmanC <41:
                        severity = 2
                    if steadmanC >=41 and steadmanC <54:
                        severity =3
                    if steadmanC >=54:
                        severity =4
                    else:
                        severity =0

                                
        else:
            print(" No temperature, Relative Humidity and/or Windspeed values currently")
        
        send_command(ser,str(servoAngles[severity]))
        print("Servo Angle : " + str(servoAngles[severity]) + degree_sign)
        time.sleep(3600)

       

if __name__ == "__main__":
    main()
