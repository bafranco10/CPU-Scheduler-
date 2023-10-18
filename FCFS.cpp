// FILE: FCFS.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for FCFS that contains all functions needed to run the FCFS algorithm and given flags
//

#include "FCFS.h"
#include "PCB_Class.h"

using namespace std;

FCFS::FCFS(){
}

FCFS::~FCFS(){
}

void FCFS::fcfsSchedule(bool verbose, PCB_Class& pcb, int tag){
    PCB_Class::PCB block;
    int earliestArrival,cpuTime = 0;
    int initSize = pcb.queueSize(pcb.initQueue);

    // keeps looping until all processes are in doneQueue
    while(pcb.queueSize(pcb.doneQueue)!=initSize){

        // if initQueue not empty then check if a process is ready and put it into readyQueue
        if(!pcb.queueEmpty(pcb.initQueue)){
            pcb.queueTagSort(pcb.initQueue,tag);
            pcb.makeReady(pcb.initQueue,cpuTime);
        }

        // if readyQueue is empty, but initQueue isn't then change cpuTime to arrival of next process
        if(pcb.queueEmpty(pcb.readyQueue) && !pcb.queueEmpty(pcb.initQueue) ){
            pcb.queueTagSort(pcb.initQueue,tag);
            cpuTime = pcb.findTagPCB(pcb.initQueue,pcb.ARRIVAL_TAG).arrivalTime;
        }
        // process can be done
        else{
            block = pcb.getPCB(pcb.readyQueue);
        
            block.waitTime = cpuTime - block.arrivalTime;

            cpuTime += block.burstTime;

            block.exitTime = cpuTime;

            pcb.popQueue(pcb.readyQueue);
            pcb.pushQueue(block, pcb.doneQueue);
        }
    }
    printOutput(verbose, pcb);
}

void FCFS::printOutput(bool verbose, PCB_Class& pcb){
    
    PCB_Class::PCB block;
    int totalWait = 0, wait;
    int processes = pcb.queueSize(pcb.doneQueue);
    
    pcb.queueTagSort(pcb.doneQueue,pcb.PID_TAG);

    while(!pcb.queueEmpty(pcb.doneQueue)){
        block = pcb.getPCB(pcb.doneQueue);
        cout << "\nP_" << block.pid;

        wait = block.waitTime;
        totalWait += wait;
        cout << "\tWait: " << wait;

        if(verbose){
            verboseOutput(block);
        }

        pcb.popQueue(pcb.doneQueue);
    }
    cout << "\n\tAverage Wait: " << (totalWait/(float) processes) << endl; 
}

void FCFS::verboseOutput(PCB_Class::PCB block){
    cout << " \tCPU Entered: " << (block.waitTime + block.arrivalTime)
        << " CPU Left: " << block.exitTime;
}
