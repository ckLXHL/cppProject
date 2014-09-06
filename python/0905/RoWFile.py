#!/usr/bin/env python

"conclude from file write and read"

import readTextFile
import makeTextFile

def RoWFile():
    'read and write select function'
    while True:
        print 'what do you want? \nread a text file choose 1\nmake a text file choose 2'
        choose = raw_input('select a num')
        if choose == '1':
            readTextFile.readTextFile()
            break
        elif choose == '2':
            makeTextFile.makeTextFile()
            break
        else:
            print 'error input'

'main function'
if __name__ == '__main__':
    RoWFile()
