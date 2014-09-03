#!/usr/bin/env python
1 + 2 * 4
a = 1
b = 'caokai'
c = 3.5
def conj():
    st = raw_input("enter something\n")
    if st == 'a':
        print a
        return True
    elif st == 'b':
        print b
        return True
    elif st == 'c':
        print c
        return True
    else:
        print 'no this variable'
        return False
while conj():
    print
