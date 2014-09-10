#!/usr/bin/env python

def run(year):
    if (year % 4 == 0) and (year % 100 != 0) or (year % 400 == 0):
        return True
    else:
        return False

if __name__ == '__main__':
    print run(1992)
    print run(1996)
    print run(2000)
    print run(1967)
    print run(1900)
    print run(2400)

