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

    // separates 4 values in a line based on blanks
    preBlank = fileLine.find(UNDERLINE);
    postBlank = fileLine.find(BLANK,preBlank);
    currentPCB.pid = atoi(fileLine.substr(preBlank+1,postBlank).c_str());
    
    preBlank = skipBlanks(fileLine,postBlank);
    postBlank = fileLine.find(BLANK,preBlank+1);
    currentPCB.arrivalTime = atoi(fileLine.substr(preBlank,postBlank).c_str());

    preBlank = skipBlanks(fileLine,postBlank);
    postBlank = fileLine.find(BLANK,preBlank+1);
    currentPCB.burstTime = atoi(fileLine.substr(preBlank,postBlank).c_str());

    preBlank = skipBlanks(fileLine,postBlank);
    postBlank = fileLine.length();
    currentPCB.priority = atoi(fileLine.substr(preBlank,postBlank).c_str());

    currentPCB.waitTime = 0;
    currentPCB.exitCounter = 0;
    currentPCB.exitTime = 0;
    currentPCB.enterTime = 0;
    currentPCB.isFirst = false;

    pushQueue(currentPCB, initQueue);

    return !loadErrorCheck(currentPCB);
}

bool PCB_Class::loadErrorCheck(PCB_Class::PCB block){
    bool error = false;

    if(block.pid < 0){
        cout << "\tERROR: Pid of P_" << block.pid << " must be a non-negative integer\n";
        error = true;
    }
    if(block.arrivalTime < 0){
        cout << "\tERROR: Arrival time of P_" << block.pid << " must be a non-negative integer\n";
        error = true;
    }
    if(block.burstTime <= 0){
        cout << "\tERROR: CPU burst of P_" << block.pid << " must be a non-negative integer\n";
        error = true;
    }
    if(block.priority > 100 || block.priority < 0){
        cout << "\tERROR: Priority of P_" << block.pid << " must be an integer from 0 to 100\n";
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

void PCB_Class::makeReadySJF(queue<PCB>& queue, int cpuTime){
    int size = queueSize(queue);
    PCB block;

    // push the next available process in initQueue into readyQueue
    for(int i=0;i<size;i++){
        block = getPCB(queue);
        if(block.arrivalTime <= cpuTime){
            block.enterTime = cpuTime;  // Set the time when the process entered the readyQueue
            pushQueue(block, readyQueue);
            popQueue(queue);
        }
        else{
            pushQueue(block, queue);
            popQueue(queue);
        }      
    }
} 

void PCB_Class::printReadyQueue() {
  queue<PCB> tempQueue = readyQueue;
    
    while (!tempQueue.empty()) {
      PCB block = tempQueue.front();
        tempQueue.pop();
	
        // Print the information of each PCB in the readyQueue
        cout << "P_" << block.pid << " Arrival Time: " << block.arrivalTime << " Burst Time: " << block.burstTime << " Priority: " << block.priority << endl;
    }
}

void PCB_Class::makeReadyRR(queue<PCB>& inputQueue, int cpuTime) {
    int size = queueSize(inputQueue);
    bool first = true;  // Set the first element of tempQueue to true
    // Create a temporary queue to hold the processes to be moved
    queue<PCB> tempQueue;

    for (int i = 0; i < size; i++) {
        PCB block = getPCB(inputQueue);
        if (block.arrivalTime <= cpuTime) {
            // Process is ready, move it to the temporary queue
            pushQueue(block, tempQueue);
        } else {
            // Process is not ready, keep it in the original queue
            pushQueue(block, inputQueue);
        }
        popQueue(inputQueue);
    }

    // Set isFirst flag to true for the first element in tempQueue
    if (!tempQueue.empty()) {
        PCB& firstBlock = tempQueue.front();
        firstBlock.isFirst = true;
    }

    // Move all processes from the temporary queue to the readyQueue
    while (!tempQueue.empty()) {
        PCB block = tempQueue.front();
        cout << "is first: " << block.isFirst << endl;
        pushQueue(block, readyQueue);
        tempQueue.pop();
    }
}

void PCB_Class::printInitQueue() {
    // Iterate through the elements in the initQueue and print their contents
    cout << "Init Queue: ";
    queue<PCB> tempQueue = initQueue;
    while (!tempQueue.empty()) {
        PCB block = tempQueue.front();
        cout << "P" << block.pid << " (Arrival Time: " << block.arrivalTime << ", Burst Time: " << block.burstTime << ") ";
        tempQueue.pop();
    }
    cout << endl;
}