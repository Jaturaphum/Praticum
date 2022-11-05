##
import serial
import time

while True:
    try : 
        ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
        break
    except :
        print("Wait...")
        time.sleep(0.2);
while True: 

    if ser.inWaiting() > 0:
        msg = ser.read(ser.inWaiting())
        ser.flushInput()
        print(msg.decode())
    time.sleep(0.2)