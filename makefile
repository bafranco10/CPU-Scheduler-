// roundRobin.h
// Round Robin Interface
//Brian Franco Armando Bautista Estefan Mora

#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include <iostream>
#include <fstream>
#include <queue>
#include "PCB_Class.h" // Include the PCB_Class header

using namespace std;

class roundRobin {
private:
    int cpuTime;
    int timeQuantum;

public:
    roundRobin(int quantum); // Constructor that takes the time quantum as a parameter

    ~roundRobin(); // Destructor

    void startRoundRobin(bool verbose);

    void printOutput(bool verbose);

    void verboseOutput();

};

#endif // ROUNDROBIN_H
