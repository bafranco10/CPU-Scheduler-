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
void roundRobin::rrSchedule(bool verbose, int quantum, PCB_Class& pcb) {
    PCB_Class::PCB block;
    int cpuTime = 0;
    int initSize = pcb.queueSize(pcb.initQueue);
    bool processRunning = false;
    pcb.printInitQueue();
    cout << "that was pcb" << endl;

    // Keep looping until all processes are in doneQueue
    while (pcb.queueSize(pcb.doneQueue) != initSize) {
        // Move all ready processes from initQueue to readyQueue
        int initQueueSize = pcb.queueSize(pcb.initQueue);
        for (int i = 0; i < initQueueSize; ++i) {
            PCB_Class::PCB firstProcess = pcb.getPCB(pcb.initQueue);
            if (firstProcess.arrivalTime <= cpuTime) {
                pcb.pushQueue(firstProcess, pcb.readyQueue);
                // Make sure to remove the process from initQueue
                pcb.popQueue(pcb.initQueue);
            }
        }

        // If readyQueue is empty, move to the next ready process
        if (!pcb.queueEmpty(pcb.readyQueue)) {
            block = pcb.getPCB(pcb.readyQueue);

            cout << "P" << block.pid << " Enter " << cpuTime << endl;
            pcb.printReadyQueue();

            if (block.burstTime > quantum) {
                block.burstTime -= quantum;
                cout << "process: " <<block.pid << " " << block.burstTime <<endl;
                processRunning = true; // Mark a process as running

                calcWait(block, cpuTime);

                cpuTime += quantum;

                block.exitTime = cpuTime;
                block.exitCounter++;

                pcb.pushQueue(block, pcb.readyQueue);
                pcb.popQueue(pcb.readyQueue);
            } else {
                int newQuantum = block.burstTime;
                block.burstTime = 0; // Process completes
                processRunning = true; // Mark a process as running

                calcWait(block, cpuTime);

                cpuTime += newQuantum; // This line might need adjustment

                block.exitTime = cpuTime;
                block.exitCounter++;

                pcb.pushQueue(block, pcb.doneQueue);
                pcb.popQueue(pcb.readyQueue);
            }

            cout << "P" << block.pid << " Exit " << block.exitTime << endl;
            processRunning = false; // Reset the flag when a process exits
        }
    }
    printOutput(verbose, pcb);
}

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
}*/
 
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
