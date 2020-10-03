#include "Process.hpp"

shAlgo::Process::Process(){
    this->PID = 666;
    this->name = "void";
    this->priority = 1;
    this->expectedBT = 0;
    this->initBT = 0;
    this->arrivalTimePoint = 0;
    this->completionTimePoint = 0;
    this->expired = false;

    prev = nullptr;
    next = nullptr;
}

//PID, name, BT
shAlgo::Process::Process(ui PID, const char* name, ui arrivalTimePoint, ui expectedBT){
    this->PID = PID;
    this->name = name;
    this->priority = 1;
    this->expectedBT = expectedBT;
    this->initBT = expectedBT;
    this->arrivalTimePoint = arrivalTimePoint;
    this->completionTimePoint = 0;
    this->expired = false;

    prev = nullptr;
    next = nullptr;
}

//PID, name, BT, priority
shAlgo::Process::Process(ui PID, const char* name, ui arrivalTimePoint, ui expectedBT, ui priority){
    this->PID = PID;
    this->name = name;
    this->priority = priority;
    this->expectedBT = expectedBT;
    this->initBT = expectedBT;
    this->arrivalTimePoint = arrivalTimePoint;
    this->completionTimePoint = 0;
    this->expired = false;

    prev = nullptr;
    next = nullptr;
}

//get PID
const shAlgo::ui& shAlgo::Process::getPID() const{
    return this->PID;
}

//get ProcessName
const char* shAlgo::Process::getProcessName() const {
    return this->name;
}

//get Expected Burst Time
shAlgo::ui& shAlgo::Process::getExpectedBT() {
    return this->expectedBT;
}

//get Priority level
const shAlgo::ui& shAlgo::Process::getPriority() const {
    return this->priority;
}

//get arrival time
const shAlgo::ui& shAlgo::Process::getArrivalTimePoint() const {
    return this->arrivalTimePoint;
}

//get completion time
shAlgo::ui& shAlgo::Process::getCompletionTimePoint() {
    return this->completionTimePoint;
}

bool& shAlgo::Process::getExpire(){
    return expired;
}

const shAlgo::ui& shAlgo::Process::getInitBT() const{
    return this->initBT;
}