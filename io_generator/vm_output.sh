#!/bin/bash
gcc ../scheduler.c -DFRMGNR -o scheduler
for p in FIFO SJF RR PSJF ;do
    for i in {1..5} ;do
        echo "----------------------"$p"_"$i"----------------------------"
        dmesg --clear
        ./scheduler < "../input/"$p"_"$i".txt" 1> "../output/"$p"_"$i"_stdout.txt"
        dmesg | grep Project1 > "../output/"$p"_"$i"_dmesg.txt"
    done
done
rm ./scheduler