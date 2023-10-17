#ifndef FCFS_H
#define FCFS_H

#include "PCB_Class.h"

using namespace std;

class FCFS{

    public:
        FCFS();
        ~FCFS();

        // takes in a PCB_Class object and the verbose flag and then schedules a queue using FCFS
        void fcfsSchedule(bool verbose, PCB_Class& pcb);
        

    protected:

    private:
        // takes in a PCB_Class object and the verbose flag and then prints out the doneQueue
        void printOutput(bool verbose, PCB_Class& pcb);

        // takes in a PCB and prints out its CPU enter and exit times
        void verboseOutput(PCB_Class::PCB block);
};

#endif // FCFS_H
