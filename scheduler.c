#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include "header/mylib.h"
const char* type_name[NUMBER_OF_TYPE] = {"FIFO","RR","SJF","PSJF"};

int main(int argc,char *argv[]){
   
    char policy_name[MAX_SCHEDULER_NAME];
    scanf("%s",policy_name);
    // determine the type
    int policy_type = 0;
    for(int i=0 ; i<= NUMBER_OF_TYPE ; i++ ){
        if(i==NUMBER_OF_TYPE){
            fprintf(stderr,"Invalid type of scheduling policy\n");
            return 1;
        }
        else if(strcmp(policy_name, type_name[i])==0){
            policy_type = i;
            break;
        }
    }
    
    // use core 0 for scheduler
    USE_CPU(0);
    fflush(stdin);

    #ifdef FRMGNR
        char *route[NUMBER_OF_TYPE] = {"../FIFO","../RR","../SJF","../PSJF"};
    #else
        char *route[NUMBER_OF_TYPE] = {"./FIFO","./RR","./SJF","./PSJF"};
    #endif
    
    // according the type to branch to each way
    switch(policy_type){
        case FIFO:
            execl(route[FIFO], route[FIFO], NULL);
            break;
        case RR:
            execl(route[RR], route[RR], NULL);
            break;
        case SJF:
            execl(route[SJF], route[SJF], NULL);
            break;
        case PSJF:
            execl(route[PSJF], route[PSJF], NULL);
            break;
    }
    return 0;
}