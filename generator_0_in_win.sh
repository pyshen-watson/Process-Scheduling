#!/bin/bash
echo "----------------------TIME_MEASUREMENT----------------------------"
sudo ./scheduler < "input/TIME_MEASUREMENT.txt" 1> "output/TIME_MEASUREMENT_stdout.txt" 2> "output/TIME_MEASUREMENT_dmesg.txt"