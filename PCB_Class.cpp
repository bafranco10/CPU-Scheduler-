// FILE: PCB_Class.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for PCB_Class that contains all functions needed to access PCBs and queues of PCBs
//

#include "PCB_Class.h"
#include <iostream>
#include <queue>
#include <strings.h>

using namespace std;

PCB_Class::PCB_Class(){
}

PCB_Class::~PCB_Class(){
}

void PCB_Class::pushQueue(PCB block, queue<PCB>& queue){
    queue.push(block);
}

void PCB_Class::popQueue(queue<PCB>& queue){
    queue.pop();
}

PCB_Class::PCB PCB_Class::getPCB(queue<PCB>& queue){
    return queue.front();
}

bool PCB_Class::queueEmpty(queue<PCB>& queue){
    return queue.empty();
}

int PCB_Class::queueSize(queue<PCB>& queue){
    return queue.size();
}

void PCB_Class::swapQueues(queue<PCB>& queue1, queue<PCB>& queue2){
    queue1.swap(queue2);
}

PCB_Class::PCB PCB_Class::findTagPCB(queue<PCB>& queue, int tag){
    PCB block = getPCB(queue), tempBlock;
    int size = queueSize(queue);

    tempBlock = block;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);

        // sets tempBlock on a different comparison based on the tag
        if(tag==PID_TAG){
            if(block.pid < tempBlock.pid) tempBlock = block;
        }
        else if(tag==ARRIVAL_TAG){
            if(block.arrivalTime < tempBlock.arrivalTime) tempBlock = block;
        }
        else if(tag==BURST_TAG){
            if(block.burstTime < tempBlock.burstTime) tempBlock = block;
        } 
        else if(tag==PRIORITY_TAG){
            if(block.priority > tempBlock.priority) tempBlock = block;
        }

        pushQueue(block, queue);
    } 
    return tempBlock; 
}

void PCB_Class::queueTagSort(queue<PCB>& queue, int tag){
    PCB block;
    while(!queueEmpty(queue)){
        block = findTagPCB(queue,tag);
        pushQueue(block, sortQueue);
        removeBlock(block, queue);
    }

    swapQueues(sortQueue, queue);

    for(int i=0;i<queueSize(sortQueue);i++) popQueue(sortQueue);
}

void PCB_Class::removeBlock(PCB block, queue<PCB>& queue){
    int size = queueSize(queue);
    PCB tempBlock;

    for(int i=0;i<size;i++){
        tempBlock = getPCB(queue);
        if(block.pid!=tempBlock.pid){
            pushQueue(tempBlock, queue);
            popQueue(queue);
        }
        else{
            popQueue(queue);
        }      
    }
}

void PCB_Class::makeReady(queue<PCB>& queue, int cpuTime){
    int size = queueSize(queue);
    PCB block;

    // push the next available process in initQueue into readyQueue
    for(int i=0;i<size;i++){
        block = getPCB(queue);
        if(block.arrivalTime<=cpuTime){
            pushQueue(block, readyQueue);
            popQueue(queue);
            break;
        }
        else{
            pushQueue(block, queue);
            popQueue(queue);
        }      

    }
}