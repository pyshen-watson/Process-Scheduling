#!/bin/bash
for p in FIFO SJF RR PSJF ;do
    for i in {1..5} ;do
    	sudmesg --clear
        echo "----------------------"$p"_$i----------------------------"
        sudo ./scheduler < "input/"$p"_$i.txt" 1> "output/"$p"_"$i"_stdout.txt" 2> "output/"$p"_"$i"_dmesg.txt"
    done
done