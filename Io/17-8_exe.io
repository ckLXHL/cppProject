#!/usr/bin/env io
List myAverage := method(
	avr := 0.0
	cnt := 0
	self foreach(i, if(i type == "Number", avr = avr + i; cnt = cnt + 1))
	if(cnt == 0, Exception raise("Number cnt is 0"))
	avr = avr / cnt
)
Buf := list(1, 2, 3, 4, 5)
Buf myAverage() println
buf := list(4, "xuije", "caokai", 3)
buf myAverage() println
buf = list("caokai")
buf myAverage() println
