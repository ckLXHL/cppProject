#!/usr/bin/env python

from isprime import isprime2
from getfactors import getfactors
def suY(num):
    if isprime2(num):
        return [num]
    primeList = []
    
    for x in getfactors(num):
        if not isprime2(x): continue
        while num != 1 and num % x == 0:
            primeList.append(x)
            num /= x
    return primeList

if __name__ == '__main__':
    print suY(20)
