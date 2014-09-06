#!/usr/bin/env python

'makeTextFile.py -- create text file'

import os

'make this a function'
def makeTextFile():
    # get filename
    while True:
        fname = raw_input('Enter file name: ')
        try:
            fobj = open(fname, 'w')
        except IOError, e:
            print '***file open Error!', e
        else:
            break
    
    # get file content (text) lines
    all = []
    print "\nEnter lines ('.' by itself to quit).\n"
    
    # loop until user terminates input
    while True:
        entry = raw_input('> ')
        if entry == '.':
            break
        else:
            all.append(entry)
    
    # write lines to file with proper line-ending
    fobj.write('\n'.join(all))
    fobj.close()
    print 'DONE!'

if __name__ == '__main__':
    makeTextFile()
