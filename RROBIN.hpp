#ifndef SH_ROBIN
#define SH_ROBIN
#include <iostream>
#include <iomanip>
#include "Q.hpp"
#include "Process.hpp"

//Simple RR algo with Queue that follows FCFS

namespace shAlgo{
    typedef unsigned int ui;

    class ROBIN{
        protected:

        bool isPremptive;
        ui iterator;
        shQ processQ;
        ui currentTimePoint;
        ui startTimePoint;
        ui stopTimePoint;
        ui updatePeriod;
        ui notifPeriod;
        ui totalProcesses;
        Process** processBuffer; //hold process for different arrival time
        Process* runningProcess; //current running process
        ui timeQuanta; //process slicing time

        //printing States of Algo at different Time Intervals
        void initialState();
        void finalState();

        public:

        //default ctor
        ROBIN();

        //ctor with number of processes, timeQuanta
        ROBIN(int totalProcess, ui timeQuanta);

        //fill process buffer
        void insertProcess(Process* p);

        //run scheduling Algo based on ProcessBuffer.
        void run();

    };

};


#endif