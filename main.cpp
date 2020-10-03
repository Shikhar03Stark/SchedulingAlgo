#include <iostream>
#include "FCFS.hpp"
#include "SJF.hpp"
#include "PRIOR.hpp"
#include "RROBIN.hpp"

int main(){
    /*
    //non-preemptive FCFS Scheduler
    shAlgo::FCFS scheduler(5);

    scheduler.insertProcess(0, new shAlgo::Process(1, "A", 0, 3));
    scheduler.insertProcess(1, new shAlgo::Process(2, "B", 1, 2));
    scheduler.insertProcess(2, new shAlgo::Process(3, "C", 2, 2));
    scheduler.insertProcess(3, new shAlgo::Process(4, "D", 3, 1));
    scheduler.insertProcess(5, new shAlgo::Process(5, "E", 5, 2));

    scheduler.run(true);
    */

   /*
    //non-preemptive SJF on BT Scheduler
    shAlgo::SJF scheduler(5);

    scheduler.insertProcess(new shAlgo::Process(1, "A", 0, 3));
    scheduler.insertProcess(new shAlgo::Process(2, "B", 1, 2));
    scheduler.insertProcess(new shAlgo::Process(3, "C", 2, 2));
    scheduler.insertProcess(new shAlgo::Process(4, "D", 3, 1));
    scheduler.insertProcess(new shAlgo::Process(5, "E", 5, 2));

    scheduler.run();
    */

    /*
    //preemptive SJF on BT Scheduler
    shAlgo::SJF scheduler(5, true);

    scheduler.insertProcess(new shAlgo::Process(1, "A", 0, 6));
    scheduler.insertProcess(new shAlgo::Process(2, "B", 1, 2));
    scheduler.insertProcess(new shAlgo::Process(3, "C", 2, 3));
    scheduler.insertProcess(new shAlgo::Process(4, "D", 3, 1));
    scheduler.insertProcess(new shAlgo::Process(5, "E", 5, 2));

    scheduler.run();
    */

   /*
   //non-preemptive priority Scheduler
   shAlgo::PRIOR scheduler(5);

    scheduler.insertProcess(new shAlgo::Process(1, "A", 0, 3, 1));
    scheduler.insertProcess(new shAlgo::Process(2, "B", 1, 2, 2));
    scheduler.insertProcess(new shAlgo::Process(3, "C", 2, 3, 2));
    scheduler.insertProcess(new shAlgo::Process(4, "D", 3, 1, 1));
    scheduler.insertProcess(new shAlgo::Process(5, "E", 5, 2, 3));

    scheduler.run();
    */

   /*
   //preemptive priority Scheduler
   shAlgo::PRIOR scheduler(5, true);

    scheduler.insertProcess(new shAlgo::Process(1, "A", 0, 5, 3));
    scheduler.insertProcess(new shAlgo::Process(2, "B", 1, 2, 2));
    scheduler.insertProcess(new shAlgo::Process(3, "C", 2, 3, 2));
    scheduler.insertProcess(new shAlgo::Process(4, "D", 3, 2, 1));
    scheduler.insertProcess(new shAlgo::Process(5, "E", 5, 2, 3));

    scheduler.run();
    */

    //Round Robin with FCFS ReadyQ
    shAlgo::ROBIN scheduler(5, 2);

    scheduler.insertProcess(new shAlgo::Process(1, "A", 0, 3, 3));
    scheduler.insertProcess(new shAlgo::Process(2, "B", 1, 3, 2));
    scheduler.insertProcess(new shAlgo::Process(3, "C", 2, 1, 2));
    scheduler.insertProcess(new shAlgo::Process(4, "D", 3, 2, 1));
    scheduler.insertProcess(new shAlgo::Process(5, "E", 5, 3, 3));

    scheduler.run();    
    
    return 0;
}