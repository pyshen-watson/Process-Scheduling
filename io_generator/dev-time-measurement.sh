#!/bin/bash
echo "----------------------TIME_MEASUREMENT----------------------------"
gcc ../scheduler.c -DFRMGNR -o scheduler
./scheduler < "../input/TIME_MEASUREMENT.txt" 1> "../output/TIME_MEASUREMENT_stdout.txt" 2> "../output/TIME_MEASUREMENT_dmesg.txt"
rm ./scheduler