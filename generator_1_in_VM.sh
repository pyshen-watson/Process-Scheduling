#!/bin/bash
for p in FIFO SJF RR PSJF ;do
    for i in {1..5} ;do
        echo "----------------------"$p"_$i----------------------------"
        sudo dmesg --clear
        sudo ./scheduler < "input/"$p"_$i.txt" 1> "output/"$p"_"$i"_stdout.txt"
        sudo dmesg | grep Project1 > "output/"$p"_"$i"_dmesg.txt"
    done
done