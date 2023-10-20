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

// handles SJF and SRTF sorting, sort calculations are then passed into print function
void SJF::sjfSchedule(bool verbose, bool preemption, PCB_Class& pcb) {
    
    int cpuTime = 0;
    PCB_Class::PCB currentProcess;
    bool isProcessRunning = false;

    // if nonpreemptive, pass in the made fcfs function with the tag 
    if (!preemption) {

        FCFS fcfs;
        fcfs.fcfsSchedule(verbose, pcb, pcb.BURST_TAG);
        return;

    }

    pcb.queueTagSort(pcb.initQueue, pcb.ARRIVAL_TAG);

    while (!pcb.queueEmpty(pcb.initQueue) || !pcb.queueEmpty(pcb.readyQueue) || isProcessRunning) {

        pcb.makeReadySJF(pcb.initQueue, cpuTime);
        pcb.printReadyQueue();

        if (!pcb.queueEmpty(pcb.readyQueue)) {
            if (isProcessRunning) {
                PCB_Class::PCB shortestJob = pcb.findTagPCB(pcb.readyQueue, pcb.BURST_TAG);
                if (shortestJob.burstTime < currentProcess.burstTime) {
                    pcb.pushQueue(currentProcess, pcb.readyQueue);
                    currentProcess = shortestJob;
                    pcb.removeBlock(currentProcess, pcb.readyQueue);
                }
            } 
            
            // if there is no process running, frab from ready queue
            else {
                currentProcess = pcb.findTagPCB(pcb.readyQueue, pcb.BURST_TAG);
                pcb.removeBlock(currentProcess, pcb.readyQueue);
                isProcessRunning = true;
            }
        }

        // implementing a tempQueue for constantly updating the ready queue
        std::queue<PCB_Class::PCB> tempQueue;
        while (!pcb.queueEmpty(pcb.readyQueue)) {
            PCB_Class::PCB processInQueue = pcb.getPCB(pcb.readyQueue);
            processInQueue.waitTime++;
            tempQueue.push(processInQueue);
            pcb.popQueue(pcb.readyQueue);
        }

        // swap tempqueue and actual queue
        while (!tempQueue.empty()) {
            pcb.pushQueue(tempQueue.front(), pcb.readyQueue);
            tempQueue.pop();
        }

        if (isProcessRunning) {
            currentProcess.burstTime--;

            if (currentProcess.burstTime == 0) {
                currentProcess.exitTime = cpuTime + 1;  // set the exitTime when the process is completed
                pcb.pushQueue(currentProcess, pcb.doneQueue); 
                isProcessRunning = false;
            }

        }

        cpuTime++;
    }

    printOutput(verbose, pcb);
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


void SJF::verboseOutput(PCB_Class::PCB block) {
        cout << "\tCPU Entered: " << block.enterTime;
        cout << "\tCPU Left: " << block.exitTime;

}