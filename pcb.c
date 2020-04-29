#define _GNU_SOURCE
#include "header/pcb.h"
#include <stdio.h>
PCB *whofirst(PCB *a, PCB *b){
    if(a->runtime < b->runtime)
        return a;
    else if(a->runtime > b->runtime)
        return b;
    else if(a->readytime < b->readytime)
        return a;
    else if(a->readytime > b->readytime)
        return b;
    else if(a->id < b->id)
        return a;
    else
        return b;
 }
PCB *createPCB(int a, int b, int c, int d){
    PCB* newnode = (PCB*) malloc(sizeof(PCB));
    newnode->id = a;
    newnode->pid = b;
    newnode->readytime = c;
    newnode->runtime = d;
    return newnode;
 }
void Insert(PCB *heap[], int *entry, PCB *p){
    (*entry)++;
    heap[*entry] = p;
    int current = *entry;
    int parent, left, right;
    PCB *t, *winner;
    while(current != 1){
        parent = current / 2;
        left = parent * 2;
        right = parent * 2 + 1;
       

        if(right == *entry + 1 ){
            winner = whofirst(heap[left], heap[parent]);
            if( winner == heap[left]){
                SWAP(heap[left] , heap[parent]);
                current = parent;
            }
            else
                current = 1;
        }

        else{
            winner = whofirst(heap[left],heap[right]);
            winner = whofirst(winner,heap[parent]);

            if(winner == heap[parent])
                current = 1;
            else if(winner == heap[left]){
                SWAP(heap[left],heap[parent]);
                current = parent;
            }
            else {
                SWAP(heap[right],heap[parent]);
                current = parent;
            }
        }

    }
    
    #ifdef DEBUG
    printf("Insert => ");
    for(int i=1;i<=*entry;i++)
    printf("[P%d %d] ", heap[i]->id, heap[i]->runtime);
    printf("\n");
    #endif
    
    return;
 }
PCB *Extract(PCB *heap[], int *size){
    /* size = how many elements */

    PCB *out = heap[1], *t;
    heap[1] = heap[*size];
    *size -= 1;
    int cur = 1, left = 2, right = 3;
    while(right < *size){
        if(heap[cur]->runtime < heap[left]->runtime && heap[cur]->runtime < heap[right]->runtime)
            break;
        else{
            if(heap[left]->runtime <= heap[right]->runtime){
                SWAP(heap[left],heap[cur]);
                cur = left;
            }

            else{
                SWAP(heap[cur],heap[right]);
                cur = right;
            }
            left = cur * 2;
            right = left + 1;
        }
    }
    
    if(*size==2){
        if(whofirst(heap[1],heap[2])==heap[2]){
            SWAP(heap[1],heap[2]);
        }
    }

    #ifdef DEBUG
    printf("Extract => ");
    for(int i=1;i<=*size;i++)
        printf("[P%d %d] ", heap[i]->id, heap[i]->runtime);
    printf("\n");
    #endif

    return out;
 }


