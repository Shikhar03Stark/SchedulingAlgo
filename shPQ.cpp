#include "shPQ.hpp"

shAlgo::shPQ::shPQ(){
    head = nullptr;
    size = 0;
    comp = PRIORITY;
}

shAlgo::shPQ::shPQ(basis comp){
    head = nullptr;
    size = 0;
    this->comp = comp;
}

shAlgo::Process* shAlgo::shPQ::getMin(){
    if(head){
        return head;
    }
    return nullptr;
}

void shAlgo::shPQ::push(Process* p){
    if(!head){
        head = p;
        ++size;
    }
    else{
        if(comp == basis::BURST){
            if(head->getInitBT() > p->getInitBT()){
                p->next = head;
                head = p;
                ++size;
                return;
            }
            auto temp = head;
            while(temp->next != nullptr){
                if(temp->getInitBT() >= p->getInitBT()){
                    break;
                }
                temp = temp->next;
            }

            //insertAfter temp
            p->next = temp->next;
            temp->next = p;

            ++size;

        }
        else{
            //priority based
            if(head->getPriority() < p->getPriority()){
                p->next = head;
                head = p;
                ++size;
                return;
            }
            auto temp = head;
            while(temp->next != nullptr){
                if(temp->getPriority() < p->getPriority()){
                    break;
                }
                temp = temp->next;
            }

            //insertAfter temp
            p->next = temp->next;
            temp->next = p;
            ++size;
        }
    }
}

void shAlgo::shPQ::pop(){
    if(size>0){
        auto p = head;
        head = head->next;
        p->next = nullptr;
        --size;
        //not deleting process poped for nullptr issues later and preemptive
    }
}


const int shAlgo::shPQ::getSize(){
    return size;
}