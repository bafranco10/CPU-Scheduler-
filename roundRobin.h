// FILE: roundRobin.h
// Brian Franco, Armando Bautista, Estefan Mora
// OS, Fall 2023, Transy U
// Round Robin Interface

#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include <iostream>
#include <fstream>
#include <queue>
#include "PCB_Class.h" // Include the PCB_Class header

using namespace std;

class roundRobin {
    public:
    
        roundRobin(); 
        ~roundRobin(); // Destructor
        
        void rrSchedule(bool verbose, int quantum, PCB_Class& pcb);
        void calcWait(PCB_Class::PCB& block, int cpuTime);
    
        void printOutput(PCB_Class& pcb);
};

#endif // ROUNDROBIN_H
