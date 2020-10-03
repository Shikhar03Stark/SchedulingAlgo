#include "FCFS.hpp"

shAlgo::FCFS::FCFS(ui totalProcess):processQ(){
    iterator = 0;
    currentTimePoint = 0;
    startTimePoint = 0;
    stopTimePoint = 0;
    updatePeriod = 1;
    notifPeriod = 1;
    this->totalProcesses = totalProcess;
    processBuffer = new std::pair<shAlgo::ui, Process*>[totalProcess];
}

shAlgo::FCFS::FCFS(ui totalProcess, ui notifyPeriod, ui updatePeriod = 1):processQ(){
    iterator = 0;
    currentTimePoint = 0;
    startTimePoint = 0;
    stopTimePoint = 0;
    this->updatePeriod = updatePeriod;
    this->notifPeriod = notifyPeriod;
    this->totalProcesses = totalProcess;
    processBuffer = new std::pair<shAlgo::ui, Process*>[totalProcess];
}

void shAlgo::FCFS::insertProcess(ui arrivalTime, shAlgo::Process* p){
    if(iterator < totalProcesses){
        processBuffer[iterator] = {arrivalTime, p};
        stopTimePoint += p->getExpectedBT();
        ++iterator;
    }
}

void shAlgo::FCFS::currentState(){
    //std::cout << std::setw(18) <<"Current Time : " << std::setw(18) << currentTimePoint << std::endl;
    std::cout << std::setw(18) << "Executed | ";
    processQ.print();
}

void shAlgo::FCFS::run(bool update = true){
    //give intial info about all process in Pbuffer
    std::cout << std::setw(18) << "T=0";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getProcessName();
    }
    std::cout << std::endl;

    //PID
    std::cout << std::setw(18) << "PID";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getPID();
    }
    std::cout << std::endl;
    

    //Arrival Time
    std::cout << std::setw(18) << "ArTime";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getArrivalTimePoint();
    }
    std::cout << std::endl;
    
    //Burst Time
    std::cout << std::setw(18) << "BrTime";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getExpectedBT();
    }
    std::cout << std::endl << std::endl;;
    
    while(currentTimePoint <= stopTimePoint){
        //least AT, push to queue
        if(update && (currentTimePoint % notifPeriod == 0))
            std::cout << std::setw(18) << "T=" << currentTimePoint << std::endl;
        for(ui i = 0; i<totalProcesses; i++){
            if(processBuffer[i].first == currentTimePoint){
                processQ.push(processBuffer[i].second);
                std::cout << std::setw(18) <<"PID:" << processBuffer[i].second->getPID() << " pushed in Ready Queue" << std::endl;
            }
        }

        if(update && (currentTimePoint % notifPeriod == 0))
            currentState();

        //running queue execution
        if(processQ.getFront()){
            if(processQ.getFront()->getExpectedBT() > updatePeriod){
                processQ.getFront()->getExpectedBT() -= updatePeriod;
            }
            else{
                processQ.getFront()->getExpire() = true;
                processQ.getFront()->getCompletionTimePoint() = currentTimePoint+1;
                processQ.pop();
            }
        }
        std::cout << std::endl;
        currentTimePoint+=updatePeriod;
    }

    double avgWaitingTime = 0, avgTurnTime = 0;

    //FCFS exit status
    std::cout << std::setw(18) << "T=" << stopTimePoint;
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getProcessName();
    }
    std::cout << std::endl;

    //PID
    std::cout << std::setw(18) << "PID";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getPID();
    }
    std::cout << std::endl;
    

    //Arrival Time
    std::cout << std::setw(18) << "Arrival Time";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getArrivalTimePoint();
    }
    std::cout << std::endl;
    
    //completion Time
    std::cout << std::setw(18) << "Completion Time";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getCompletionTimePoint();
    }
    std::cout << std::endl;

    //turn Around Time
    std::cout << std::setw(18) << "Turn Around Time";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getCompletionTimePoint() - processBuffer[i].second->getArrivalTimePoint();
        avgTurnTime += processBuffer[i].second->getCompletionTimePoint() - processBuffer[i].second->getArrivalTimePoint();
    }
    std::cout << std::endl;

    //waiting Time
    std::cout << std::setw(18) << "Wating Time";
    for(ui i = 0; i<totalProcesses;i++){
        std::cout << std::setw(18) << processBuffer[i].second->getCompletionTimePoint() - processBuffer[i].second->getArrivalTimePoint() - processBuffer[i].second->getInitBT();
        avgWaitingTime += processBuffer[i].second->getCompletionTimePoint() - processBuffer[i].second->getArrivalTimePoint() - processBuffer[i].second->getInitBT();
    }
    std::cout << std::endl;

    std::cout << std::setw(18) << "Average Waiting Time : " << avgWaitingTime/totalProcesses << std::endl;
    std::cout << std::setw(18) << "Average Turn Around Time : " << avgTurnTime/totalProcesses << std::endl;
}