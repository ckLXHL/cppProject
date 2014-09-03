#!/usr/bin/env python
def sumof5():
    num = 0
    num += int(raw_input('input 1st\n'))
    num += int(raw_input('input 2nd\n'))
    num += int(raw_input('input 3rd\n'))
    num += int(raw_input('input 4th\n'))
    num += int(raw_input('input 5th\n'))
    print num
def avgof5():
    num = 0
    num += int(raw_input('input 1st\n'))
    num += int(raw_input('input 2nd\n'))
    num += int(raw_input('input 3rd\n'))
    num += int(raw_input('input 4th\n'))
    num += int(raw_input('input 5th\n'))
    print num / 5.0
def IsP():
    num = int(raw_input('input a num\n'))
    if num < 0:
        print 'minus'
    elif num > 0:
        print 'plus'
    else:
        print 'zero'
def PrintEach():
    st = raw_input('input a string\n')
    for a in st:
        print a,
def GusNum():
    while True:
        num = int(raw_input('input a num\n'))
        if num < 20:
            print 'too small\n'
        elif num > 20:
            print 'too big\n'
        else:
            print 'get it!!!!\n'
            break
menu = 0
while menu != 6:
    print '1.sum of five numvers'
    print '2.average of five numbers'
    print '3.Is positive, negative, or zero'
    print '4.print each of charactor'
    print '5.guess the number'
    print '6.Quit'
    st = raw_input('select a number: ')
    while not st.isdigit() or int(st) > 6 or int(st) <1:
        st = raw_input('input error, try again: ')
    menu = int(st)
    if menu == 1:
        sumof5()
    elif menu == 2:
        avgof5()
    elif menu == 3:
        IsP()
    elif menu == 4:
        PrintEach()
    elif menu == 5:
        GusNum()
