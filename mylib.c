#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "header/mylib.h"
#include "header/pcb.h"
int compare(const void *a, const void *b){
    PCB *x = (PCB*) a;
    PCB *y = (PCB*) b;
    if(x->readytime > y->readytime)           return 1;
    else if (x->readytime < y->readytime)     return -1;
    else                                      return 0;
 }

void unit_time() {
    volatile unsigned long i;
    for (i = 0; i < UNIT_TIME; i++);
    return;
  }

void create_process(void *vpcb, int timeAmount){
    
    PCB *pcb = (PCB*) vpcb;
    pid_t ppid = getpid();

    
    if(pcb->start_time == 0){
            #ifdef SYSCALL_AVAILABLE
                    pcb -> start_time = syscall(548);
            #else
                    pcb -> start_time = (long) time(NULL);
            #endif
     }
    pid_t PID = fork();

    // child process
    if (PID == 0) {
        USE_CPU(1);
        for (int i = 0; i < timeAmount; i++)
            unit_time();
        if(pcb->runtime == timeAmount)
            kill(ppid, SIGFNS);
        else
            kill(ppid,SIGTERM);
        exit(0);
    }

    // parent process
    else if (PID > 0) {
        if(pcb->pid == 0)   pcb->pid = PID;
        return;
    }

    // error case
    else{ 
        fprintf(stderr,"fork() error\n");
        return;
     }
 }