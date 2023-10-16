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
    currentPCB.id = atoi(fileLine.substr(preBlank+1,postBlank).c_str());
    
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

    pushQueue(currentPCB, newQueue);
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

bool PCB_Class::queueEmpty(queue<PCB> queue){
    return queue.empty();
}