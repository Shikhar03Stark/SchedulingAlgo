#include "Q.hpp"

shAlgo::shQ::shQ(){
    this->back = nullptr;
    this->front = nullptr;
    this->size = 0;
}

void shAlgo::shQ::push(Process *p){
    if(size == 0){
        front = p;
        back = p;
    }
    else{
        back->prev = p;
        p->next = back;
        back = p;
    }
    ++size;
}

void shAlgo::shQ::pop(){
    if(size == 0){
        //exception
        return;
    }
    else{
        if(back == front){
            //delete back;
            //fix memory leak
            back = nullptr;
            front = nullptr;
        }
        else{
            front = front->prev;
            //delete front->next;
            //fix above memory leak
            front->next = nullptr;
        }
        --size;
    }
}

const shAlgo::ui shAlgo::shQ::getSize() const{
    return size;
}

shAlgo::Process* shAlgo::shQ::getFront(){
    return front;
}

shAlgo::Process* shAlgo::shQ::getBack() {
    return back;
}

void shAlgo::shQ::print(){
    auto itr = front;
    while(itr != nullptr){
        std::cout << std::setw(6) << itr->getProcessName();
        itr = itr->prev;
    }
    std::cout << std::endl;
}

