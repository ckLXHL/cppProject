#!/usr/bin/env python

def score(sc):
    print 'class is',
    if(sc >= 90):
        print 'A'
    elif(sc >= 80):
        print 'B'
    elif(sc >= 70):
        print 'C'
    elif(sc >= 60):
        print 'D'
    else:
        print 'F'

if __name__ == '__main__':
    score(75)
