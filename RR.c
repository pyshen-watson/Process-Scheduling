#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include "header/mylib.h"
#include "header/pcb.h"

int N;
char ID[MAX_PROCESS_NAME];
PCB pcb[MAX_N_OF_PROCESS];
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
    if(signo == SIGTERM)
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

    // one round one unit time
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
            //fprintf(stderr,"%d P%d run %d, left %d\n", cur, runNow->id, timeAmount, runNow->runtime);
            pcbptr = (pcbptr + 1) % N;
        }
        unit_time();
     }

    PROCESS_TABLE();

    return 0;
 }