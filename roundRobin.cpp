// FILE: roundRobin.cpp
// Brian Franco, Armando Bautista, Estefan Mora
// OS, Fall 2023, Transy U
// Round Robin Implementation

#include "roundRobin.h"
#include "PCB_Class.h"
#include <queue>

roundRobin::roundRobin() {

}

roundRobin::~roundRobin() {
    // Destructor
}
///*
// doesn't work yet, but prints out something
void roundRobin::rrSchedule(bool verbose, int quantum, PCB_Class& pcb){
    PCB_Class::PCB block;
    int earliestArrival,cpuTime = 0;
    int initSize = pcb.queueSize(pcb.initQueue);

    // keeps looping until all processes are in doneQueue
    while(pcb.queueSize(pcb.doneQueue)!=initSize){

        // if initQueue not empty then check if a process is ready and put it into readyQueue
        if(!pcb.queueEmpty(pcb.initQueue)){
            pcb.queueTagSort(pcb.initQueue,pcb.PID_TAG);
            pcb.makeReady(pcb.initQueue,cpuTime);
        }

        // if readyQueue is empty, but initQueue isn't then change cpuTime to arrival of next process
        if(pcb.queueEmpty(pcb.readyQueue) && !pcb.queueEmpty(pcb.initQueue) ){
            pcb.queueTagSort(pcb.initQueue,pcb.PID_TAG);
            cpuTime = pcb.findTagPCB(pcb.initQueue,pcb.ARRIVAL_TAG).arrivalTime;
        }
        // process can be done
        else{
            block = pcb.getPCB(pcb.readyQueue);

            cout << "P" << block.pid << "Enter" << cpuTime << endl;

            if (block.burstTime > quantum) {
                block.burstTime -= quantum;

                // block.enterTime = cpuTime;
                
                calcWait(block,cpuTime);

                cpuTime += quantum;

                block.exitTime = cpuTime;
                block.exitCounter++;

                pcb.pushQueue(block, pcb.readyQueue);
                pcb.popQueue(pcb.readyQueue);
            } 
            else{
                block.burstTime -= block.burstTime;
                // block.enterTime = cpuTime;

                calcWait(block,cpuTime);

                cpuTime += block.burstTime;

                block.exitTime = cpuTime;
                block.exitCounter++;

                pcb.pushQueue(block, pcb.doneQueue);
                pcb.popQueue(pcb.readyQueue);
            }

            cout << "P" << block.pid << "Exit" << block.exitTime << endl;
        }
    }
    printOutput(verbose, pcb);
}//*/

/*cout << "exit time" << block.exitTime << endl;
                if (block.arrivalTime > 0 && block.exitCounter == 0 ) {
                    block.waitTime += block.enterTime - block.exitTime - block.arrivalTime; 
                }
                else {
                block.waitTime += block.enterTime - block.exitTime; 
                }

void roundRobin::rrSchedule(bool verbose, int quantum, PCB_Class& pcb){

        if(block.arrivalTime <= cpuTime){
        
            block.waitTime = cpuTime - block.arrivalTime;

            cpuTime += block.burstTime;

            block.exitTime = cpuTime;

            pcb.popQueue(pcb.readyQueue);
            pcb.pushQueue(block, pcb.doneQueue);
        }
}//*/
 
void roundRobin::printOutput(bool verbose, PCB_Class& pcb) {
    if (!verbose) {
        PCB_Class::PCB block;
        int totalWait = 0, wait;
        int processes = pcb.queueSize(pcb.doneQueue);

        pcb.queueTagSort(pcb.doneQueue,pcb.PID_TAG);

        while (!pcb.queueEmpty(pcb.doneQueue)) {
            block = pcb.getPCB(pcb.doneQueue);
            cout << "\nP_" << block.pid;

            wait = block.waitTime;
            totalWait += wait;
            cout << "\tWait: " << wait;

            pcb.popQueue(pcb.doneQueue);
        }
        cout << "\n\tAverage Wait: " << (totalWait / (float)processes) << endl;
    } else {
        verboseOutput();
    }
}

void roundRobin::verboseOutput() {
   
}

void roundRobin::calcWait(PCB_Class::PCB& block, int cpuTime){
    if(block.exitCounter==0){
        block.waitTime += cpuTime - block.arrivalTime;
    }
    else{
        block.waitTime += cpuTime - block.exitTime;
    }
}