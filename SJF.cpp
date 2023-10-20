// FILE: SJF.cpp
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Implementation for SJF that contains all functions needed to run the SJF algorithm and given flags
//

#include "SJF.h"
#include "FCFS.h"
#include "PCB_Class.h"
#include <map>
using namespace std;

SJF::SJF(){
}

SJF::~SJF(){
}

// somewhat working, verbose is not correct and gives wrong answer if processes arrive at same time
//  print it says the wait time is the cpu time where it stopped executing
void SJF::sjfSchedule(bool verbose, bool preemption, PCB_Class& pcb) {
    if (!preemption) {
        // Non-preemptive SJF using FCFS functions
        FCFS fcfs;
        fcfs.fcfsSchedule(verbose, pcb, pcb.BURST_TAG);
        return;
    }

    int cpuTime = 0;
    PCB_Class::PCB currentProcess;
    bool isProcessRunning = false;

    pcb.queueTagSort(pcb.initQueue, pcb.ARRIVAL_TAG);

    while (!pcb.queueEmpty(pcb.initQueue) || !pcb.queueEmpty(pcb.readyQueue) || isProcessRunning) {

        // Move processes from initQueue to readyQueue based on arrival time
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
            } else {
                currentProcess = pcb.findTagPCB(pcb.readyQueue, pcb.BURST_TAG);
                pcb.removeBlock(currentProcess, pcb.readyQueue);
                isProcessRunning = true;
            }
        }

        // update process wait times in ready queue
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

            // debug output 
            cout << "Debug: Process P_" << currentProcess.pid << " - CPU Time: " << cpuTime
                 << ", Arrival Time: " << currentProcess.arrivalTime
                 << ", Wait Time: " << currentProcess.waitTime
                 << ", Burst Time: " << currentProcess.burstTime << endl;

            if (currentProcess.burstTime == 0) {
                // Set the exitTime when the process is completed
                currentProcess.exitTime = cpuTime + 1;  // Update the exitTime
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
        << "\tCPU Entered: " << block.enterTime;
        cout << "\tCPU Left: " << block.exitTime;

}





