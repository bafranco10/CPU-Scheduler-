// CPU_Scheduler.cpp
// Need 2 files for each scheduling type and for the PCB datatype, plus a driver, so at least 11 files
// https://cplusplus.com/reference/queue/queue/ 10-15-2023

#include "PCB_Class.h"
#include "FCFS.h"
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/* In addition to taking in the file, the program should take in
--type {FCFS|SJF|Priority|RR} (FCFS is the default)
--preemptive (not is the default)
--quanta # (10 is the default)
--file NAME (sched.in is the default)
--verbose (not is the default) for extra info

ID      Arrival_Time      Total_CPU_Burst        Priority

ID is P_#
*/

const string TYPE="--type", PREEMPTIVE="--preemptive", QUANTA="--quanta",FILE_NAME="--file",VERBOSE="--verbose";
const string FIRST_COME_FIRST_SERVE="FCFS",SHORTEST_JOB_FIRST="SJF",PRIORITY="Priority",ROUND_ROBIN="RR";
const string DEFAULT_TYPE=FIRST_COME_FIRST_SERVE,DEFAULT_QUANTA="10",DEFAULT_FILE="sched.in";
const int FLAGS=5,TYPE_FLAG=0,PREEMPTIVE_FLAG=1,QUANTA_FLAG=2,FILE_FLAG=3,VERBOSE_FLAG=4;

bool errorCheck(bool *flags, char **argv, string type, string quanta);

int main(int argc, char **argv){
		PCB_Class pcb;
		FCFS fcfs;
		ifstream inputFile;
		string fileLine;
		string type = DEFAULT_TYPE, quanta = DEFAULT_QUANTA, fileName = DEFAULT_FILE;
		bool flags[FLAGS];

		for(int i=0;i<FLAGS;i++){
			flags[i]=false;
		}

        // sets flags
        // check for ----type find TYPE then if found, but not TYPE, error
        // handle no input after type, file, or quanta
        // handle multiple sapces in input file
        // for file, check if priority is 1-100, if arrival and burst are >0 
		for(int i=0;i<argc;i++){
            string argument = argv[i];
			if(argument == TYPE){
                type = argv[i+1];
                flags[TYPE_FLAG] = true;
			}
			if(argument == PREEMPTIVE){
                flags[PREEMPTIVE_FLAG] = true;
			}
			if(argument == QUANTA){
                quanta = argv[i+1];
                flags[QUANTA_FLAG] = true;
			}
			if(argument == FILE_NAME){
                fileName = argv[i+1];
                flags[FILE_FLAG] = true;
			}
			if(argument == VERBOSE){
                flags[VERBOSE_FLAG] = true;
			}
		}
		
		if(!errorCheck(flags, argv, type, quanta)){
			inputFile.open(fileName);
			if(inputFile){
			    while(!inputFile.eof()){
			        getline(inputFile, fileLine);
					pcb.loadPCB(fileLine);
				}
				inputFile.close();
			}
			else{
				cout << "\tERROR: File not opened\n";
				return 0;
			}
		}
		else{
			return 0;
		}

		
		/*
		while(!pcb.queueEmpty(pcb.waitQueue)){
			cout << "\t\nP_" << pcb.getPCB(pcb.waitQueue).id;
			pcb.popQueue(pcb.waitQueue);
		}
		//*/

		if(type==FIRST_COME_FIRST_SERVE){
			fcfs.fcfsSchedule(flags[VERBOSE_FLAG],pcb);
		}
		else if(type==SHORTEST_JOB_FIRST){

		}
		else if(type==PRIORITY){

		}
		else if(type==ROUND_ROBIN){

		}




	return 0;
}

// checks that valid inputs were given
bool errorCheck(bool *flags, char **argv, string type, string quanta){
	bool error = false;
	if(flags[PREEMPTIVE_FLAG] && type == FIRST_COME_FIRST_SERVE){
		cout << "\tERROR: FCFS cannot be preemptive\n";
		error = true;
	}
	if(type==ROUND_ROBIN && !flags[PREEMPTIVE_FLAG]){
		cout << "\tERROR: RR must be preemptive\n";
		error = true;
	}
	if(type!=ROUND_ROBIN && flags[QUANTA_FLAG]){
		cout << "\tERROR: Only RR should use a quanta specification\n";
		error = true;
	}
	if(type!=ROUND_ROBIN && type!=FIRST_COME_FIRST_SERVE && type!=PRIORITY && type!=SHORTEST_JOB_FIRST){
		cout << "\tERROR: Invlaid type. This program supports FCFS, SJF, Priority and RR\n";
		error = true;
	}
	if(flags[QUANTA_FLAG] && (atoi(quanta.c_str()) <= 0)){
		cout << "\tERROR: Quanta must be a positive number\n";
		error = true;
	}
	return error;		
}