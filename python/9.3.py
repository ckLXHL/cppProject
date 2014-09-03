#!/usr/bin/env python
def foo(debug=True):
    if  debug:
        print 'in debug mode'
    print 'done'
foo()
foo(False)

class FooClass(object):
    """my very first class: FooClass"""
    version = 0.1
    def __init__(self, nm='Jphn Doe'):
        "constructor"
        self.name = nm
        print 'Create a class instance for', nm
    def showname(self):
        "display instance attribute and class name"
        print 'Your name is', self.name
        print 'My name is', self.__class__.__name__
    def showver(self):
        "display class(static) attribute"
        print self.version
    def addMe2Me(self, x):
        'apply _ operation to argument'
        return (x + x)
foo2 = FooClass()
foo2.showname()
foo2.showver()

import sys
sys.stdout.write('Hello World!\n')
print sys.platform
print sys.version
