// FILE: SJF.h
// A Bautista, B Franco, E Mora
// OS, Fall 2023, Transy U
//
// Interface for SJF that contains all functions needed to run the SJF algorithm and given flags
//

#ifndef SJF_H
#define SJF_H

#include "PCB_Class.h"

using namespace std;

class SJF{

    public:
        SJF();
        ~SJF();

        // takes in a PCB_Class object, the verbose flag, and the preemption flag and then schedules using SJF
        void sjfSchedule(bool verbose, bool preemption, PCB_Class& pcb);
        

    protected:

    private:
        // takes in a PCB_Class object and the verbose flag and then prints out the doneQueue
        void printOutput(bool verbose, PCB_Class& pcb);

        // takes in a PCB and prints out its CPU enter and exit times
        void verboseOutput(PCB_Class::PCB block);
};

#endif // SJF_H
