# FILE: makefile
# A Bautista, B Franco, E Mora
# OS, Fall 2023, Transy U
#
# makefile for 
#

CPU_Scheduler: CPU_Scheduler.o PCB_Class.o FCFS.o
	g++ CPU_Scheduler.o PCB_Class.o FCFS.o -o CPU_Scheduler
	
CPU_Scheduler.o: CPU_Scheduler.cpp
		g++ -c CPU_Scheduler.cpp

PCB_Class.o: PCB_Class.cpp PCB_Class.h
	g++ -c PCB_Class.cpp

FCFS.o: FCFS.cpp FCFS.h
	g++ -c FCFS.cpp

roundRobin.o: roundRobin.cpp roundRobin.h 
	g++ -c roundRobin.cpp

Priority.o: Priority.cpp Priority.h
	g++ -c Prioirty.cpp

SJF.o: SJF.cpp SJF.h
	g++ -c SJF.cpp
