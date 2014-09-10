#!/usr/bin/env python

def coins(money):
    twentyFive = int(money / 0.25)
    money = money % 0.25
    ten = int(money / 0.1)
    money = money % 0.1
    five = int(money / 0.05)
    money = money % 0.05
    one = int(money / 0.01)
    return twentyFive + ten + five + one

if __name__ == '__main__':
    print coins(0.76)
