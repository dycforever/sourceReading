#!/bin/bash
make clean && make
gdb -x gdb.cmd test_conf
