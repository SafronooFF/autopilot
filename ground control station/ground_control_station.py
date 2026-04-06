from tkinter import *
import serial

window = Tk()
window.geometry('250x200')

def up_elevon():
    ser.write(b'\x01')
    ser.flush() #немедленная отправка
    print(ser.readline())

def down_elevon():
    ser.write(b'\x0A')
    ser.flush() #немедленная отправка
    print(ser.readline())

def neutral_elevon():
    ser.write(b'\x0B')
    ser.flush() #немедленная отправка
    print(ser.readline())

try:
    ser = serial.Serial('/dev/ttyACM0', baudrate=115200, timeout=1)
except:
    ser = None
#ser.close()

label2 = Label(text = 'Проверка элевонов', font=("Arial", 12))
label2.grid(row = 0, column = 0)

btn = Button(text='Элевоны вверх', command = up_elevon)
btn.grid(row = 1, column = 0, padx=10, pady= 5)

btn = Button(text='Элевоны вниз')
btn.grid(row = 2, column = 0, padx=10, pady= 5)

btn = Button(text='Элевоны нейтраль')
btn.grid(row = 3, column = 0, padx=10, pady=5)

btn = Button(text='Отцеп')
btn.grid(row = 1, column = 1, padx=10, pady=5)

window.mainloop()
