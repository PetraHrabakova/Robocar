import serial as ser
from serial import Serial

if __name__ == '__main__':
    ser = ser.Serial('/dev/ttyACM0', 115200, timeout=1)
    ser.flush()

    while True:
        data = ser.readline().strip()
        print(data)
        if data != b'':
            distance = data
            if distance < 400 and distance > 500:
               ser.write(b'a')
            if distance < 400:
               ser.write(b'b')
            if distance > 500:
               ser.write(b'c')
