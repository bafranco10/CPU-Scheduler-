// FILE: FCFS.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for FCFS that contains all functions needed to run the FCFS algorithm and given flags
//

#ifndef FCFS_H
#define FCFS_H

#include "PCB_Class.h"

using namespace std;

class FCFS{

    public:
        FCFS();
        ~FCFS();

        // takes in a PCB_Class object and the verbose flag and then schedules using FCFS based on the tag
        void fcfsSchedule(bool verbose, PCB_Class& pcb, int tag);
        
    private:
        // takes in a PCB_Class object and the verbose flag and then prints out the doneQueue
        void printOutput(bool verbose, PCB_Class& pcb);

        // takes in a PCB and prints out its CPU enter and exit times
        void verboseOutput(PCB_Class::PCB block);
};

#endif // FCFS_H
