#!/usr/bin/env io
ErL := List
ErL dim := method(x, y,
	for(i, 1, y, append(Range 1 to(x) asList))
	return self
)
ErL printAll := method(
	self foreach(i, 
		i foreach(j, j print; " " print)
		writeln
	)
	return self
)
ErL set := method(x, y, tmp,
	self at(y) atPut(x, tmp)
	return self
)
ErL get := method(x, y,
	self at(y) at(x) println
	return self
)
nee := ErL
nee dim(4, 4) printAll()
