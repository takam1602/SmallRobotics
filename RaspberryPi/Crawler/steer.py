#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 10 19:47:03 2021

@author: hizatate
#PCからWiFi使って遠隔操作するためのやつ。
"""
import os
import sys, termios, atexit
from select import select

# save the terminal settings
fd = sys.stdin.fileno()
new_term = termios.tcgetattr(fd)
old_term = termios.tcgetattr(fd)

# new terminal setting unbuffered
new_term[3] = (new_term[3] & ~termios.ICANON & ~termios.ECHO)

# switch to normal terminal
def set_normal_term():
    termios.tcsetattr(fd, termios.TCSAFLUSH, old_term)

# switch to unbuffered terminal
def set_curses_term():
    termios.tcsetattr(fd, termios.TCSAFLUSH, new_term)

def putch(ch):
    sys.stdout.write(ch)

def getch():
    return sys.stdin.read(1)

def getche():
    ch = getch()
    putch(ch)
    return ch

def kbhit():
    dr,dw,de = select([sys.stdin], [], [], 0)
    return dr != []     # ここだけ修正

if __name__ == '__main__':
    atexit.register(set_normal_term)
    set_curses_term()

    while 1:
        if kbhit():
            ch = getch()
            break
        sys.stdout.write('.')

    print('done:'+ch)

R = 100
L = 100

print("Start")
while True:
    if kbhit():  
        key = ord(getch())
        if key == 101:  
            #print("LeftUP_e")
            L += 5
        if key == 100:
            #print("LeftDOWN_d")
            L -= 5
        if key == 114:
            #print("RightUP_r")
            R += 5
        if key == 102:
            #print ("RightDOWN_f")
            R -= 5
        if key == 27:
            break
    else :
        print(L,R)
        os.system('clear')
print("END")