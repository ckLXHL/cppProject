#!/usr/bin/env io
i := 1
while(i <= 11, i println; i = i + 1) 
"This one goes up to 11" println 
"This one goes up to 12" println
for(i, 1, 11, 2, i println)
"This one goes up to 11" println
for(i, 1, 2, 1, i println, "extra argument")
for(i, 1, 2, i println, "extra argument")
i = 1
	loop(
			if(i < 20) 
			then(i = i + 1, i println) 
			else("finish" println; break)
		)
