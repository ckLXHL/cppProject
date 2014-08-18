#!/usr/bin/env io
OperatorTable addAssignOperator(":", "atPutNumber")
curlyBrackets := method(
	r := Map clone
	call message arguments foreach(arg,
		r doMessage(arg)
	)
	return r
)
Map atPutNumber := method(
	self atPus(
		call evalArgAt(0) asMutable removePrefix("\"") removeSuffix("\""),
		call evalArgAt(1)
	)
)
s := File with("phonebook.txt") openForReading contents
phoneNumbers := doString(s)
phoneNumbers keys println
phoneNumbers values println
