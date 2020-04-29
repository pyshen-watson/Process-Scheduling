#!/bin/bash
echo "----------------------TIME_MEASUREMENT----------------------------"
sudo dmesg --clear
sudo ./scheduler < "input/TIME_MEASUREMENT.txt" 1> "output/TIME_MEASUREMENT_stdout.txt"
dmesg | grep Project1 > "output/TIME_MEASUREMENT_dmesg.txt"