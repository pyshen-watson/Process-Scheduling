all:  clean
	gcc scheduler.c -o scheduler
	gcc ./policy/FIFO.c ./src/mylib.c ./src/pcb.c -o FIFO
	gcc ./policy/SJF.c ./src/mylib.c ./src/pcb.c -o SJF
	gcc ./policy/RR.c ./src/mylib.c ./src/pcb.c -o RR
	gcc ./policy/PSJF.c ./src/mylib.c ./src/pcb.c -o PSJF
syscall: 
	gcc scheduler.c -o scheduler
	gcc ./policy/FIFO.c ./src/mylib.c ./src/pcb.c -DSYSCALL_AVAILABLE -o FIFO
	gcc ./policy/SJF.c ./src/mylib.c ./src/pcb.c -DSYSCALL_AVAILABLE -o SJF
	gcc ./policy/RR.c ./src/mylib.c ./src/pcb.c -DSYSCALL_AVAILABLE -o RR
	gcc ./policy/PSJF.c ./src/mylib.c ./src/pcb.c -DSYSCALL_AVAILABLE -o PSJF
init: clean clear
clean:
	@rm -f  scheduler FIFO SJF RR PSJF a.out
clear:
	@rm -f ./output/*.txt
test0:
	./scheduler < ./input/TIME_MEASUREMENT.txt
test1:
	./scheduler < ./input/FIFO_1.txt
test2:
	./scheduler < ./input/PSJF_2.txt
test3:
	./scheduler < ./input/RR_3.txt
test4:
	./scheduler < ./input/SJF_4.txt			