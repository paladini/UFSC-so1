/*
 * Queue.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: paladini
 */
 
#ifndef QUEUE_CPP_
#define QUEUE_CPP_
#include "Queue.h"
 
using namespace BOOOS;

Queue::Queue() {
    _length = 0;
    //this->_head = 0;
}

// finalize queue attributes
Queue::~Queue(){}

// Check if the element is already on the queue
void Queue::insert(Element * elem) {
    if (elem == 0) {
        throw -1;
    }

    if(_length > 0) {
        Element *last = _head.prev();

        last->next(elem);
        elem->prev(last);
        elem->next(_head.next());
        _head.next()->prev(elem);
        _head.prev(elem);
    } else {
        _head.next(elem);
        _head.prev(elem);
        elem->next(elem);
        elem->prev(elem);
    }

    _length++;
}

Queue::Element * Queue::remove() {

    // Fila vazia
    if(_length == 0) {
        throw -1;
    }

    Element *trueHead = _head.next();
    Element *last = _head.prev();

    _head.next(trueHead->next());
    _head.next()->prev(last);
    last->next(_head.next());
    
    _length--;
    return trueHead;
}
 
#endif /* QUEUE_CPP_ */