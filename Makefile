all: scheduler policy
alld: scheduler
	gcc FIFO.c mylib.c pcb.c -DSYSCALL_AVAILABLE -o FIFO
	gcc SJF.c mylib.c pcb.c -DSYSCALL_AVAILABLE -o SJF
	gcc RR.c mylib.c pcb.c -DSYSCALL_AVAILABLE -o RR
	gcc PSJF.c mylib.c pcb.c -DSYSCALL_AVAILABLE -o PSJF
scheduler:
	gcc scheduler.c -o scheduler
policy:
	gcc FIFO.c mylib.c pcb.c -o FIFO
	gcc SJF.c mylib.c pcb.c -o SJF
	gcc RR.c mylib.c pcb.c -o RR
	gcc PSJF.c mylib.c pcb.c -o PSJF
debug:
	gcc scheduler.c -o scheduler
	gcc FIFO.c mylib.c pcb.c -DDEBUG -o  FIFO
	gcc SJF.c mylib.c pcb.c -DDEBUG -o SJF
	gcc RR.c mylib.c pcb.c -DDEBUG -o RR
	gcc PSJF.c mylib.c pcb.c -DDEBUG -o PSJF
clean:
	@rm -f  scheduler FIFO SJF RR PSJF a.out
test:
	./scheduler < ./input/TIME_MEASUREMENT.txt
