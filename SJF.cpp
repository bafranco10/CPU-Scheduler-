// FILE: SJF.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for SJF that contains all functions needed to run the SJF algorithm and given flags
//

#include "SJF.h"
#include "FCFS.h"
#include "PCB_Class.h"

using namespace std;

SJF::SJF(){
}

SJF::~SJF(){
}

void SJF::sjfSchedule(bool verbose, bool preemption, PCB_Class& pcb) {
    FCFS fcfs;
    PCB_Class::PCB block;
    int cpuTime = 0;
    int initSize = pcb.queueSize(pcb.initQueue); //need to initialize size of the queue to be used

    if (!preemption) {
        // non-preemptive SJF using FCFS functions
        fcfs.fcfsSchedule(verbose, pcb, pcb.BURST_TAG);
    } 

    else if (preemption) {
        while (pcb.queueSize(pcb.doneQueue) != initSize) {
            // put process in ready queue if queue is not empty
            if (!pcb.queueEmpty(pcb.initQueue)) {
                pcb.queueTagSort(pcb.initQueue, pcb.BURST_TAG);
                pcb.makeReady(pcb.initQueue, cpuTime);
            }

            // if ready queue is empty but initQueue is not, make cpuTime the arrival time of next process
            if (pcb.queueEmpty(pcb.readyQueue) && !pcb.queueEmpty(pcb.initQueue)) {
                pcb.queueTagSort(pcb.initQueue, pcb.ARRIVAL_TAG);
                cpuTime = pcb.findTagPCB(pcb.initQueue, pcb.ARRIVAL_TAG).arrivalTime;
            } 
            
            else {
                pcb.queueTagSort(pcb.readyQueue, pcb.BURST_TAG);
                block = pcb.getPCB(pcb.readyQueue);

                // preempt the following process if the current one has not finished
                if (block.arrivalTime > cpuTime) {
                    cpuTime = block.arrivalTime;
                }

                block.waitTime = cpuTime - block.arrivalTime;
                cpuTime += 1;  
                block.burstTime -= 1;

                // if process is not done, put back in ready queue
                if (block.burstTime > 0) {
                    pcb.pushQueue(block, pcb.readyQueue);
                } 
                
                else {
                    // process is done(?)
                    block.exitTime = cpuTime;
                    pcb.popQueue(pcb.readyQueue);
                    pcb.pushQueue(block, pcb.doneQueue);
                }
            }
        }

        printOutput(verbose, pcb);
    }
}





void SJF::printOutput(bool verbose, PCB_Class& pcb){
    
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

void SJF::verboseOutput(PCB_Class::PCB block){
    int cpuTime = block.waitTime + block.arrivalTime;
    cout << " \tCPU Entered: " << cpuTime
        << " CPU Left: " << (block.burstTime + cpuTime);
}