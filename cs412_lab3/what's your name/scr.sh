#!/bin/bash

for i in {1..10}
do
	echo "i: $i"
	echo -ne "%$i\$s" | ./1
	echo
	echo
done
