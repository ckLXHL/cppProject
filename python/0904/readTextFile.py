#!/usr/bin/env python

'readTextFile.py -- read and dsplay test file'
def readTextFile():
    'make this a function'
    # get filename
    fname = raw_input('Enter filename:')
    print
    # attempt to open file for reading
    try:
        fobj = open(fname, 'r')
    except IOError, e:
        print '***file open error:', e
    else:
        # display contents to the screen
        for eachLine in fobj:
            print eachLine,
        fobj.close()
if __name__ == '__main__':
    readTextFile()
