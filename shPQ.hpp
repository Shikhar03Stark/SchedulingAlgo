#ifndef SH_PQ
#define SH_PQ
#include "Process.hpp"
//singly linked Linst implementation of Min Priority Q
//top == O(1), pop = O(1), push = O(n)
//only for Process*, no template for error checking/simplicity

namespace shAlgo{
    enum basis{
        BURST,
        PRIORITY
    };
    class shPQ{
    protected:
        Process* head;
        int size;
        basis comp;
    public:
        //default ctor, basis = priority
        shPQ();

        //priority with basis
        shPQ(basis comp);

        //get Min
        Process* getMin();

        //push
        void push(Process* p);

        //pop
        void pop();

        //get size
        const int getSize();
    };
};


#endif