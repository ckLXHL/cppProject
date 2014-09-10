#!/usr/bin/env python

def displayNumType(num):
    print num, 'is',
    if isinstance(num, (int, long, float, complex)):
        print 'a number of type:', type(num).__name__
    else:
        print 'not a number at all!!'
displayNumType(-69)
displayNumType(999999999999999L)
displayNumType(98.6)
displayNumType(-5.2 + 1.9j)
displayNumType('xxx')

def displayNumType2(num):
    print num, "is",
    if type(num) == type(0):
        print 'an integer'
    elif type(num) == type(0L):
        print 'a long'
    elif type(num) == type(0.0):
        print 'a float'
    elif type(num) == type(0 + 0j):
        print 'a complex number'
    else:
        print 'not a number at all!'

displayNumType2(-69)
displayNumType2(999999999999999L)
displayNumType2(98.6)
displayNumType2(-5.2 + 1.9j)
displayNumType2('xxx')

