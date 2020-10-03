#ifndef SH_FCFS
#define SH_FCFS
#include "Q.hpp"
#include <utility>
#include <iostream>
#include <iomanip>


namespace shAlgo{
    typedef unsigned int ui;
    class FCFS{
    protected:
        ui iterator;
        shQ processQ;
        ui currentTimePoint;
        ui startTimePoint;
        ui stopTimePoint;
        ui updatePeriod;
        ui notifPeriod;
        ui totalProcesses;
        std::pair<ui, Process*> *processBuffer; //imaginative, {arrivalTime, Process Ptr}

        void currentState();
    public:
        //default ctor
        FCFS(ui totalProcess);

        //ctor with update and notifPeriod
        FCFS(ui totalProcess, ui notifyPeriod, ui updatePeriod);

        //fill Process Buffer  
        void insertProcess(ui arrivalTime, Process* p);

        //run FCFS on given process Buffer
        void run(bool update);
    };
};

#endif