#define _GNU_SOURCE
#include <stdlib.h>
typedef struct{
    int id;
    pid_t pid;
    int readytime;
    int runtime;
    long start_time;
    long end_time;
 }PCB;
#define SWAP(x,y) do{\
    (t) = (x);\
    (x) = (y);\
    (y) = (t);\
 }while(0)


void Insert(PCB *heap[], int *entry, PCB *p);
PCB *Extract(PCB *heap[], int *size);