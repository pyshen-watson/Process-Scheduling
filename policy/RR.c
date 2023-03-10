#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "../header/pcb.h"
#include "../header/mylib.h"


int N;
char ID[MAX_PROCESS_NAME];
PCB pcb[MAX_N_OF_PROCESS];
PCB *runNow;
int enable;
int finish;


void signal_routine(int signo){

    if(signo == SIGFNS){
        
		#ifdef SYSCALL_AVAILABLE
            runNow->end_time = syscall(SYS_TIME);
    		syscall(SYS_PRINTK, runNow->pid, runNow->start_time, runNow->end_time);
        #else
    		runNow->end_time = (long) time(NULL);
			fprintf(stderr, "[Project1] %d %ld %ld\n", runNow->pid, runNow->start_time, runNow->end_time);
		#endif

		enable = TRUE;
		finish++;
	}

	else if(signo == SIGTERM)
	        enable = TRUE;

    return;
 }

int main(int argc,char *argv[]){
    
    USE_CPU(0);
    INIT_DATA();
    qsort(pcb, N, sizeof(PCB), compare);
    signal(SIGFNS, signal_routine);
    signal(SIGTERM, signal_routine);
    enable = TRUE;
    finish = 0;
    int invalid = 0;
    int pcbptr = 0;
    int time_slice = 500;

    for(int cur=0 ; finish != N ; cur++){

       if( enable == TRUE){
            invalid = 0;
            while (invalid != N) {
                if(pcb[pcbptr].runtime == 0 || pcb[pcbptr].readytime > cur ){
                    pcbptr = (pcbptr + 1) % N;
                    invalid++;
                }
                else
                    break;
            }
            if(invalid == N)
                continue;
            
            runNow = &pcb[pcbptr];
            enable = FALSE;
            int timeAmount = (runNow->runtime > time_slice) ? time_slice : runNow->runtime;
            create_process( runNow, timeAmount);
            pcb[pcbptr].runtime -= timeAmount;
            pcbptr = (pcbptr + 1) % N;
         }
        unit_time();
     }

    PROCESS_TABLE();
    syscall(SYS_PRINTK, 0, 0, 0);

    return 0;
 }