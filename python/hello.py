#!/usr/bin/env python
class Human(object):
	def __init__(self, input_gender):
		self.gender = input_gender
	def printGender(self):
		print self.gender
	laugh = 'hahahahah'
	def show_laugh(self):
		print self.laugh
	def laugh_100th(self):
		for i in range(100):
			self.show_laugh()
li_lei = Human('male')
print(li_lei.gender)
li_lei.printGender()
li_lei.laugh = 'ccccc'
li_lei.show_laugh()
fu = Human('fu')
fu.show_laugh()
fu.laugh_100th()
fu.show_laugh()
[1, 2, 3, 4 ,5].__abs__
