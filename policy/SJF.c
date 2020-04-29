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
        enable = TRUE;
        finish += 1;
        #ifdef SYSCALL_AVAILABLE
                runNow -> end_time = syscall(548);
                syscall(549, runNow->pid, runNow->start_time, runNow->end_time);        
        #else
                runNow -> end_time = (long) time(NULL);
                fprintf(stderr, "[Project1] %d %ld %ld\n",runNow->pid, runNow->start_time, runNow->end_time);           
        #endif 
    }
    return;
 }

int main(int argc,char *argv[]){
    
    USE_CPU(0);
    INIT_DATA();
    qsort(pcb, N, sizeof(PCB), compare);
    signal(SIGFNS, signal_routine);

   
    int size = 0;
    int pcbptr = 0;
    enable = TRUE;
    finish = 0;
  
    // one round one unit time
    for(int cur=0 ; finish!=N ; cur++){

        while(pcbptr < N && pcb[pcbptr].readytime == cur){
            Insert(Heap,&size,&pcb[pcbptr]);
            pcbptr++; 
        }
        
        if( size != 0 && enable == TRUE){
                runNow = Extract(Heap, &size);
                enable = FALSE;
                create_process(runNow, runNow->runtime);
        }

        unit_time();
     }
    
    PROCESS_TABLE();
    
    
    return 0;
 }