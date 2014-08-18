#!/usr/bin/env io
Fib := method(i, if(i == 1 or i == 2, 1, Fib(i - 1) + Fib(i - 2)))
Fib(20) println
Fib2 := method(i, 
	res := 1
	res2 := 1
	tmp := 0
	Range 3 to(i) foreach(i, 
		res = res + res2
		tmp = res
		res = res2
		res2 = tmp)
)
Fib2(20) println
