#ifndef SH_Q
#define SH_Q
#include "Process.hpp"
#include <iostream>
#include <iomanip>
/*
Doubly Linked List implementation of Queue

*/

namespace shAlgo{
    typedef unsigned int ui;
    class shQ{
    protected:
        Process* back;
        Process* front;
        ui size;

    public:
        //default ctor
        shQ();

        //push operation
        void push(Process* p);

        //pop operation
        void pop();

        //get Size of Queue
        const ui getSize() const;

        //get Front Process Pointer
        Process* getFront();

        //get Back Process Pointer
        Process* getBack();

        //print Q, front to Back
        void print();

    };
};


#endif