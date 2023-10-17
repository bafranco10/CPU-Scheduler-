#include "PCB_Class.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

PCB_Class::PCB_Class()
{

}

PCB_Class::~PCB_Class()
{
    //dtor
}

void PCB_Class::loadPCB(string fileLine){
    size_t preBlank,postBlank;
    PCB currentPCB;

    preBlank = fileLine.find(UNDERLINE);
    postBlank = fileLine.find(BLANK,preBlank);
    currentPCB.pid = atoi(fileLine.substr(preBlank+1,postBlank).c_str());
    
    preBlank = fileLine.find(BLANK,postBlank);
    postBlank = fileLine.find(BLANK,preBlank+1);
    currentPCB.arrivalTime = atoi(fileLine.substr(preBlank,postBlank).c_str());

    preBlank = fileLine.find(BLANK,postBlank);
    postBlank = fileLine.find(BLANK,preBlank+1);
    currentPCB.burstTime = atoi(fileLine.substr(preBlank,postBlank).c_str());

    preBlank = fileLine.find(BLANK,postBlank);
    postBlank = fileLine.length();
    currentPCB.priority = atoi(fileLine.substr(preBlank,postBlank).c_str());

    currentPCB.waiting = true;

    pushQueue(currentPCB, waitQueue);
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
int PCB_Class::skipBlanks(string fileLine, int startPos){

}

int PCB_Class::earliestArrival(queue<PCB>& queue){
    PCB block = getPCB(queue);
    int size = queueSize(queue);
    int earliest = block.arrivalTime;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.arrivalTime < earliest){
            earliest = block.arrivalTime;
        }
        pushQueue(block, queue);
    } 
    return earliest; 
}

int smallestPid(queue<PCB>& queue){
    PCB block = getPCB(queue);
    int size = queueSize(queue);
    int smallest = block.pid;

    block = getPCB(queue);
    smallest = block.pid;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.pid < smallest){
            smallest = block.pid;
        }
        pushQueue(block, queue);
    } 
    return smallest;
}
int shortestJob(queue<PCB>& queue){
    PCB block = getPCB(queue);
    int size = queueSize(queue);
    int shortest = block.burstTime;

    block = getPCB(queue);
    shortest = block.burstTime;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.burstTime < shortest){
            shortest = block.burstTime;
        }
        pushQueue(block, queue);
    } 
    return shortest;
}
int highestPriority(queue<PCB>& queue){
    PCB block = getPCB(queue);
    int size = queueSize(queue);
    int highest = block.priority;

    block = getPCB(queue);
    highest = block.priority;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.priority > highest){
            highest = block.priority;
        }
        pushQueue(block, queue);
    } 
    return highest;
}