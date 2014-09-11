#!/usr/bin/env python

def getfactors(num):
    return [x for x in range(num, 0, -1) if num % x == 0]

if __name__ == '__main__':
    print getfactors(20)
