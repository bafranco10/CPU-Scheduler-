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

// for file, check if priority is 1-100, if arrival and burst are >0 
bool PCB_Class::loadPCB(string fileLine){
    size_t preBlank,postBlank;
    PCB currentPCB;
    bool loadSuccess = true;

    // ensures only blanks are in fileLine by replacing tabs
    for(int i=0;i<fileLine.length();i++){
        if(fileLine[i]==TAB){
            fileLine[i] = BLANK;
        }
    }

    preBlank = fileLine.find(UNDERLINE);
    postBlank = fileLine.find(BLANK,preBlank);
    currentPCB.pid = atoi(fileLine.substr(preBlank+1,postBlank).c_str());

    // P_3       10    15  100
    
    preBlank = skipBlanks(fileLine,postBlank);
    postBlank = fileLine.find(BLANK,preBlank+1);
    currentPCB.arrivalTime = atoi(fileLine.substr(preBlank,postBlank).c_str());

    preBlank = skipBlanks(fileLine,postBlank);
    postBlank = fileLine.find(BLANK,preBlank+1);
    currentPCB.burstTime = atoi(fileLine.substr(preBlank,postBlank).c_str());

    preBlank = skipBlanks(fileLine,postBlank);
    postBlank = fileLine.length();
    currentPCB.priority = atoi(fileLine.substr(preBlank,postBlank).c_str());

    currentPCB.waiting = true;

    cout << "Hey\n" << currentPCB.pid << endl << currentPCB.arrivalTime << endl << currentPCB.burstTime << endl << currentPCB.priority << endl; 

    pushQueue(currentPCB, waitQueue);

    return !loadErrorCheck(currentPCB);
}

bool PCB_Class::loadErrorCheck(PCB_Class::PCB block){
    bool error = false;

    if(block.pid < 0){
        cout << "\tERROR: Pid must be a non-negative integer\n";
        error = true;
    }
    if(block.arrivalTime < 0){
        cout << "\tERROR: Arrival time must be a non-negative integer\n";
        error = true;
    }
    if(block.burstTime < 0){
        cout << "\tERROR: CPU burst must be a non-negative integer\n";
        error = true;
    }
    if(block.priority > 100 || block.priority < 0){
        cout << "\tERROR: Priority must be an integer from 0 to 100\n";
        error = true;
    }

    return error;
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

int PCB_Class::skipBlanks(string& fileLine, int startPos){
    for(int i=startPos;i<fileLine.length();i++){
        if(fileLine[i]!=BLANK){
            return i;
        }
    }
    return -1;
}

void PCB_Class::swapQueues(queue<PCB>& queue1, queue<PCB>& queue2){
    queue1.swap(queue2);
}

PCB_Class::PCB PCB_Class::earliestArrival(queue<PCB>& queue){
    PCB block = getPCB(queue), earliest;
    int size = queueSize(queue);

    earliest = block;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.arrivalTime < earliest.arrivalTime){
            earliest = block;
        }
        pushQueue(block, queue);
    } 
    return earliest; 
}

PCB_Class::PCB PCB_Class::smallestPid(queue<PCB>& queue){
    PCB block = getPCB(queue), smallest;
    int size = queueSize(queue);

    smallest = block;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.pid < smallest.pid){
            smallest = block;
        }
        pushQueue(block, queue);
    } 
    return smallest;
}

PCB_Class::PCB PCB_Class::shortestJob(queue<PCB>& queue){
    PCB block = getPCB(queue), shortest;
    int size = queueSize(queue);

    shortest = block;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.burstTime < shortest.burstTime){
            shortest = block;
        }
        pushQueue(block, queue);
    } 
    return shortest;
}

PCB_Class::PCB PCB_Class::highestPriority(queue<PCB>& queue){
    PCB block = getPCB(queue), highest;
    int size = queueSize(queue);

    highest = block;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.priority > highest.priority){
            highest = block;
        }
        pushQueue(block, queue);
    } 
    return highest;
}

// 0 3 4 2 1 5
// 0 1 2 3 4 5
// may need a removePCB(pid,queue)
/*
void PCB_Class::sortPid(queue<PCB>& queue){
    queue<PCB_Class::PCB> temp;
    PCB block;
    int size = queueSize(queue);
    block = smallestPid(queue);
    smallest = block;

    for(int i=0;i<size;i++){
        block = getPCB(queue);
        popQueue(queue);
        if(block.pid < smallest.pid){
            smallest = block;
        }
        pushQueue(block, temp);
    }

    swapQueues(temp, queue);
}//*/