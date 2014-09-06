#!/usr/bin/env python
print '|', 'hej'.ljust(20), '|', \
       'hej'.rjust(20), '|',\
       'hej'.center(20), '|'
print '|', 'hej'.ljust(20, '+'), '|', \
       'hej'.rjust(20, '+'), '|',\
       'hej'.center(20, '+'), '|'
x = '   hej   '
print '|', x.lstrip(), '|',\
       x.rstrip(), '|',\
       x.strip(), '|'
x = 'xyyxyxhejyx yyx'
print '|' + x.strip('xy') + '|'
x = list('sdfdgsdg')
print ''.join(x)
small1 = 'caokai'
small2 = 'guoxiong'
small3 = 'kkk'
pieces = [small1, small2, small3]
largeString = ''
for piece in pieces:
   largeString += piece
   largeString += ' '
print largeString.strip()
print len(largeString)
largeString = ' '.join(pieces)
revwords = largeString.split()
revwords.reverse()
print ' '.join(revwords)
print ' '.join(reversed(largeString.split()))
def containsAny1(seq, aset):
   for c in seq:
       if c in aset: return True
       return False
import itertools
def containsAny2(seq, aset):
   for item in itertools.ifilter(aset.__contains__, seq):
       return True
   return False
def containsAny3(seq, aset):
   return bool(set(aset).intersection(seq))
def containsOnly(seq, aset):
   for c in seq:
       if c not in aset: return False
   return True
def containsALL(seq, aset):
   return not set(aset).difference(seq)
print containsAny1('agfdgfs','afgjkatrieajrhuag')
print containsAny2('agfdgfs','afgjkatrieajrhuag')
print containsAny3('agfdgfs','afgjkatrieajrhuag')
print containsOnly('agfdgfs','afgjkatrieajrhuag')
print containsALL('agfdgfs','afgjkatrieajrhuag')
