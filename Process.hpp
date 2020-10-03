#ifndef SH_PROCESS
#define SH_PROCESS

/*Doubly Linked List Node as a Process
*/

namespace shAlgo{
    typedef unsigned int ui;
    class Process{
    protected:
        ui PID;
        const char* name;
        ui priority;
        ui expectedBT; //milli sec
        ui initBT; //for final calculation purposes
        ui arrivalTimePoint;
        ui completionTimePoint;
        bool expired;

    public:
        Process* prev;
        Process* next;
        
        //void ctor
        Process();

        //PID, name, BT
        Process(ui PID, const char* name, ui arrivalTimePoint, ui expectedBT);

        //PID, name, BT, priority
        Process(ui PID, const char* name, ui arrivalTimePoint, ui expectedBT, ui priority);

        //get PID
        const ui& getPID() const;

        //get ProcessName
        const char* getProcessName() const;

        //get Expected Burst Time
        ui& getExpectedBT();

        //get Priority level
        const ui& getPriority() const;

        bool& getExpire();

        const ui& getArrivalTimePoint() const;

        ui& getCompletionTimePoint();

        const ui& getInitBT() const;
    };
};

#endif