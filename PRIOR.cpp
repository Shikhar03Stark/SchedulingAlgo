#include "PRIOR.hpp"

shAlgo::PRIOR::PRIOR():processQ(){
    isPreemptive = false;
    iterator = 0;
    currentTimePoint = 0;
    startTimePoint = 0;
    stopTimePoint = 0;
    notifPeroid = 1;
    updatePeriod = 1;
    totalProcesses = 0;
    processBuffer = nullptr;
    runningProcess = nullptr;
}

shAlgo::PRIOR::PRIOR(int totProcess, bool nature):processQ(){
    isPreemptive = nature;
    iterator = 0;
    currentTimePoint = 0;
    startTimePoint = 0;
    stopTimePoint = 0;
    notifPeroid = 1;
    updatePeriod = 1;
    totalProcesses = totProcess;
    processBuffer = new Process*[totalProcesses];
    runningProcess = nullptr;
}

void shAlgo::PRIOR::insertProcess(Process* p){
    if(iterator<totalProcesses){
        processBuffer[iterator] = p;
        stopTimePoint += p->getExpectedBT();
        ++iterator;
    }
}

void shAlgo::PRIOR::run(){
    initialState();

    if(isPreemptive){
        while(currentTimePoint <= stopTimePoint){
            for(int i = 0; i<totalProcesses; i++){
                if(processBuffer[i]->getArrivalTimePoint() == currentTimePoint){
                    processQ.push(processBuffer[i]);
                }
            }
            //check for context switiching
            if(runningProcess && processQ.getSize() != 0){
                auto p = processQ.getMin();
                if(p->getPriority() > runningProcess->getPriority()){
                    //switch conetext
                    auto temp = runningProcess;
                    runningProcess = p;
                    processQ.pop();
                    processQ.push(temp);

                    std::cout << "Context Switch, " << p->getPID() << " replaced " << temp->getPID() << ", T = " << currentTimePoint << std::endl;
                }
            }
            
            if(runningProcess == nullptr || runningProcess->getExpectedBT() == 0){
                if(processQ.getSize() != 0){
                    auto p = processQ.getMin();
                    processQ.pop();
                    std::cout << std::setw(18) << p->getPID() << " " << " is running, T = " << currentTimePoint << std::endl;
                    if(runningProcess){
                        runningProcess->getExpire() = true;
                        runningProcess->getCompletionTimePoint() = currentTimePoint;
                    }

                    runningProcess = p;
                }
                else{
                    if(runningProcess && runningProcess->getExpectedBT() == 0){
                        runningProcess->getCompletionTimePoint() = currentTimePoint;
                        runningProcess->getExpire() = true;
                        runningProcess = nullptr;
                    }
                    std::cout << std::setw(18) << "CPU Idle, T = " << currentTimePoint << std::endl;
                }
            }

            //update running process for next itr
            if(runningProcess)
                runningProcess->getExpectedBT() -= updatePeriod;

            currentTimePoint += updatePeriod;
        }
    }
    //non-preemptive
    else{
        while(currentTimePoint <= stopTimePoint){
            for(int i = 0; i<totalProcesses; i++){
                if(processBuffer[i]->getArrivalTimePoint() == currentTimePoint){
                    processQ.push(processBuffer[i]);
                }
            }

            //pop SJF process to running state

            if(runningProcess == nullptr || runningProcess->getExpectedBT() == 0){
                if(processQ.getSize() != 0){
                    auto p = processQ.getMin();
                    processQ.pop();
                    std::cout << std::setw(18) << p->getPID() << " " << " is running, T = " << currentTimePoint << std::endl;
                    if(runningProcess){
                        runningProcess->getExpire() = true;
                        runningProcess->getCompletionTimePoint() = currentTimePoint;
                    }

                    runningProcess = p;
                }
                else{
                    if(runningProcess && runningProcess->getExpectedBT() == 0){
                        runningProcess->getCompletionTimePoint() = currentTimePoint;
                        runningProcess->getExpire() = true;
                        runningProcess = nullptr;
                    }
                    std::cout << std::setw(18) << "CPU Idle, T = " << currentTimePoint << std::endl;
                }
            }

            //update running process for next itr
            if(runningProcess)
                runningProcess->getExpectedBT() -= updatePeriod;

            currentTimePoint += updatePeriod;
        }
    }


    finalState();
}

void shAlgo::PRIOR::initialState(){
    //Process Name
    std::cout << std::setw(18) << "Process Name : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getProcessName() << " ";
    }
    std::cout << std::endl;

    //PID
    std::cout << std::setw(18) << "Process ID : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getPID() << " ";
    }
    std::cout << std::endl;

    //arrival Time
    std::cout << std::setw(18) << "Arrival Time : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getArrivalTimePoint() << " ";
    }
    std::cout << std::endl;

    //expected BurstTime
    std::cout << std::setw(18) << "Burst Time : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getInitBT() << " ";
    }
    std::cout << std::endl;

    //Priority
    std::cout << std::setw(18) << "Priority Time : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getPriority() << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
}

void shAlgo::PRIOR::finalState(){
    double avgWaitingTime = 0, avgTurnTime = 0;

    //Process Name
    std::cout << std::setw(18) << "Process Name : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getProcessName() << " ";
    }
    std::cout << std::endl;

    //Arrival Time
    std::cout << std::setw(18) << "Arrival Time : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getArrivalTimePoint() << " ";
    }
    std::cout << std::endl;

    //Completion Time
    std::cout << std::setw(18) << "Completion Time : ";
    for(int i = 0; i<totalProcesses; i++){
        std::cout << std::setw(18) << processBuffer[i]->getCompletionTimePoint() << " ";
    }
    std::cout << std::endl;

    //turn Around Time
    std::cout << std::setw(18) << "TA Time : ";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i]->getCompletionTimePoint() - processBuffer[i]->getArrivalTimePoint() << " ";
        avgTurnTime += processBuffer[i]->getCompletionTimePoint() - processBuffer[i]->getArrivalTimePoint();
    }
    std::cout << std::endl;

    //waiting Time
    std::cout << std::setw(18) << "WT Time : ";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i]->getCompletionTimePoint() - processBuffer[i]->getArrivalTimePoint() - processBuffer[i]->getInitBT() << " ";
        avgWaitingTime += processBuffer[i]->getCompletionTimePoint() - processBuffer[i]->getArrivalTimePoint() - processBuffer[i]->getInitBT();
    }
    std::cout << std::endl;

    std::cout << std::setw(18) << "Average WT : " << avgWaitingTime/totalProcesses << std::endl;
    std::cout << std::setw(18) << "Average TA Time : " << avgTurnTime/totalProcesses << std::endl;
}