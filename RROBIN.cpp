#include "RROBIN.hpp"

shAlgo::ROBIN::ROBIN():processQ(){
    iterator=0;
    currentTimePoint=0;
    startTimePoint=0;
    stopTimePoint=0;
    updatePeriod=1;
    notifPeriod=1;
    totalProcesses=0;
    processBuffer = nullptr;
    runningProcess = nullptr;
    timeQuanta = 1;
}

shAlgo::ROBIN::ROBIN(int totalProcess, ui timeQuanta):processQ(){
    iterator=0;
    currentTimePoint=0;
    startTimePoint=0;
    stopTimePoint=0;
    updatePeriod=1;
    notifPeriod=1;
    totalProcesses = totalProcess;
    processBuffer = new Process*[totalProcesses];
    runningProcess = nullptr;
    this->timeQuanta = timeQuanta;
}

void shAlgo::ROBIN::insertProcess(Process* p){
    if(iterator<totalProcesses){
        processBuffer[iterator] = p;
        stopTimePoint += p->getInitBT();
        ++iterator;
    }
}

void shAlgo::ROBIN::run(){
    initialState();

    ui processTime = 0;
    while(currentTimePoint <= stopTimePoint){
        for(int i = 0; i<totalProcesses; i++){
            if(processBuffer[i]->getArrivalTimePoint() == currentTimePoint){
                processQ.push(processBuffer[i]);
            }
        }

        //roll Process
        if(processTime == timeQuanta){
            if(processQ.getSize() > 0){
                if(runningProcess){
                    auto p = runningProcess;
                    if(p->getExpectedBT()==0){
                        p->getCompletionTimePoint() = currentTimePoint;
                        p->getExpire() = true;
                    }

                    runningProcess = processQ.getFront();
                    processQ.pop();
                    if(p->getExpectedBT() > 0)
                        processQ.push(p);
                    if(runningProcess){
                        std::cout << "Context Switched, " << runningProcess->getPID() << " replaced " << p->getPID() << ", T = " << currentTimePoint << std::endl;
                    }
                }
            }
            else{
                if(runningProcess == nullptr)
                    std::cout << "CPU Idle, T = " << currentTimePoint << std::endl;
            }
            
            processTime = 0;
        }

        if(runningProcess == nullptr || runningProcess->getExpectedBT() == 0){
            if(runningProcess && runningProcess->getExpectedBT() == 0){
                runningProcess->getCompletionTimePoint() = currentTimePoint;
                runningProcess->getExpire() = true;
                runningProcess = nullptr;
            }
            if(processQ.getSize() > 0){
                runningProcess = processQ.getFront();
                processQ.pop();
                std::cout << std::setw(18) << runningProcess->getPID() << " is running, T = " << currentTimePoint << std::endl;
            }   
            else{
                if(runningProcess == nullptr)
                    std::cout << "CPU Idle, T = " << currentTimePoint << std::endl;
            }
        }
        
        if(runningProcess && runningProcess->getExpectedBT() == 0){
            runningProcess->getCompletionTimePoint() = currentTimePoint;
            runningProcess->getExpire() = true;
            runningProcess = nullptr;
        }


        //update running process for next itr
        if(runningProcess)
            runningProcess->getExpectedBT() -= updatePeriod;

        currentTimePoint += updatePeriod;
        if(runningProcess)
            processTime += updatePeriod;

    }
    if(runningProcess){
        runningProcess->getCompletionTimePoint() = stopTimePoint;
        runningProcess->getExpire() = true;
        runningProcess = nullptr;
    }

    finalState();
}

void shAlgo::ROBIN::initialState(){
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

    std::cout << std::endl;
}

void shAlgo::ROBIN::finalState(){
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