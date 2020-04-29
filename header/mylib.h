// this header define some constant and macro
#define UNIT_TIME 1e6
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

// define for scheduler.c
#define MAX_SCHEDULER_NAME 8
#define NUMBER_OF_TYPE     4
#define MAX_PROCESS_NAME   5
#define MAX_N_OF_PROCESS   22

// policy type
#define FIFO 0
#define RR   1
#define SJF  2
#define PSJF 3

// for lib and policy
#define FALSE              0
#define TRUE               1
#define SIGFNS             16

// input in every policy
#define INIT_DATA() do {					    \
	scanf("%d", &N);		                    \
	for (int i=0; i<N; i++){ 		            \
	    scanf("%s %d %d", ID, &pcb[i].readytime, &pcb[i].runtime);	\
        pcb[i].id = stoi(ID);                                       \
        pcb[i].pid = 0;                                             \
        pcb[i].start_time = 0;                                      \
        pcb[i].end_time = 0;                                        \
    }                                                               \
 } while(0)

#define USE_CPU(x) do{      \
    cpu_set_t mask;         \
    CPU_ZERO (&mask);       \
    CPU_SET ((x),&mask);    \
 }while(0)

#define DEBUG_TABLE() do{                                                        \
    printf("P\tPID\tStart\t\tEnd\t\tInterval\n");                                \
    printf("========================================================\n");        \
    for(int i=0; i<N ; i++)                                                      \
        printf("P%d\t%d\t%ld\t%ld\t%ld\n",pcb[i].id, pcb[i].pid,pcb[i].start_time, pcb[i].end_time, (pcb[i].end_time-pcb[i].start_time) );  \
 }while(0)

#define PROCESS_TABLE() do{                          \
    for(int i=0; i<N ; i++)                          \
        printf("P%d %d\n",pcb[i].id, pcb[i].pid);    \
 }while(0)

int stoi(char *str);
void unit_time();
int compare(const void *a, const void *b);
void create_process(void *vpcb, int timeAmount);

