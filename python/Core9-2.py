#!/usr/bin/env python

print 'I like to use the Internet for:'
for item in ['e-mail', 'net-surfing', 'homework', 'chat']:
    print item,
print

who = 'knights'
what = 'Ni!'
print 'We are the', who, 'who say', what, what, what, what
print 'We are the %s who say %s' % \
        (who, ((what + ' ') * 4))

for eachNum in [0, 1, 2]:
    print eachNum
for eachNum in range(3):
    print eachNum
foo = 'abc'
for c in foo:
    print c
for i in range(len(foo)):
    print foo[i], '(%d)' %i

squared = [x ** 2 for x in range(4)]
for i in squared:
    print i
sqdEvens = [x ** 2 for x in range(8) if not x % 2]
for i in sqdEvens:
    print i

#filename = raw_input('Enter file name: ')
#fobj = open(filename, 'r')
#data = fobj.readlines()
#fobj.close()
#for eachLine in data:
#    print eachLine

try:
    filename = raw_input('Enter file name: ')
    fobj = open(filename, 'r')
    for eachLine in fobj:
        print eachLine,
    fobj.close()
except IOError, e:
    print 'file open error:', e

