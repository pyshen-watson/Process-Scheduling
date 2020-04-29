#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include "header/mylib.h"
const char* type_name[NUMBER_OF_TYPE] = {"FIFO","RR","SJF","PSJF"};

int main(int argc,char *argv[]){
   
    char policy_name[MAX_SCHEDULER_NAME];
    scanf("%s",policy_name);
    
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

    // use core 0 for scheduler master
    USE_CPU(0);
    fflush(stdin);

    switch(policy_type){
        case FIFO:
            execl("./FIFO","./FIFO",NULL);
            break;
        case RR:
            execl("./RR","./RR",NULL);
            break;
        case SJF:
            execl("./SJF","./SJF",NULL);
            break;
        case PSJF:
            execl("./PSJF","./PSJF",NULL);
            break;
    }
    return 0;
}