#ifndef SH_SJF
#define SH_SJF
#include <iostream>
#include <iomanip>
#include "shPQ.hpp"
#include "Process.hpp"

namespace shAlgo{
    typedef unsigned int ui;
    class SJF{
        protected:

        bool isPreemptive;
        ui iterator;
        shPQ processQ;
        ui currentTimePoint;
        ui startTimePoint;
        ui stopTimePoint;
        ui updatePeriod;
        ui notifPeroid;
        ui totalProcesses;
        Process** processBuffer; //hold processes for different arrival time
        Process* runningProcess; //running process, single Core

        //printing States of Algo at different Time intervals
        void initialState();
        void finalState();

        public:
        
        //default ctor, non-preemptive, job = burstTime
        SJF();

        //default nature non-preemptive, job = burstTime
        SJF(int totalProcess, bool nature = false);

        //fill process buffer
        void insertProcess(Process* p);

        //run scheduling algo, handles both preemptive/non-preemptive
        void run();

    };
};
#endif
