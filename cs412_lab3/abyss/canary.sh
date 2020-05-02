#!/bin/bash

perl -e 'print "AB"x10000' | setarch `arch` -R ./exe
