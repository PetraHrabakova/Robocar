import curses
import serial
from serial import Serial
import time

stdscr = curses.initscr()
curses.cbreak()
stdscr.keypad(1)

stdscr.addstr(0,10, "Hit q to quit")
stdscr.refresh()

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()

    key = ''
    try:
        while key != ord('q'):
            key = stdscr.getch()
            stdscr.addch(20,25,key)
            stdscr.refresh()

            if key == curses.KEY_UP:
                stdscr.addstr(1,20,"Forward")
                ser.write(b'W')

            elif key == curses.KEY_DOWN:
                stdscr.addstr(2,20,"Backwards")
                ser.write(b'S')

            elif key == curses.KEY_LEFT:
                stdscr.addstr(3,20, "Left")
                ser.write(b'A')

            elif key == curses.KEY_RIGHT:
                stdscr.addstr(4,20, "Right")
                ser.write(b'D')
            elif key == ord('b'):
                key = stdscr.getch()
                stdscr.addstr(5,20, "Break")
                ser.write(b'B')
            elif key == ord('q'):
                stdscr.addscr.getch()
                break

    except KeyboardInterrupt:
            pass

