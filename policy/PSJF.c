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
PCB *Heap[MAX_N_OF_PROCESS];
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
    int size = 0;
    enable = TRUE;
    int pcbptr = 0;
    int time_slice = 2000;
    PCB* yet = NULL;
  
    for(int cur=0 ; finish!=N ; cur++){
        
        while(pcbptr < N && pcb[pcbptr].readytime == cur){  
            Insert(Heap, &size, &pcb[pcbptr]);
            pcbptr++;  
        }
        
        if( size != 0 && enable == TRUE){
                runNow = Extract(Heap, &size);
                if(yet != NULL){
                    Insert(Heap, &size, yet);
                    yet = NULL;
                }
                enable = FALSE;
                int timeAmount = (runNow->runtime > time_slice) ? time_slice : runNow->runtime;
                create_process(runNow, timeAmount);
                runNow->runtime -= timeAmount;

                if(runNow->runtime != 0){
                    if(size == 0)
                        Insert(Heap, &size, runNow);
                    else
                        yet = runNow;
                }
        }

        unit_time();
     }

    PROCESS_TABLE();
    syscall(SYS_PRINTK, 0, 0, 0);


    return 0;
 }