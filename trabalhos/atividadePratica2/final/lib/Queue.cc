/* Emmanuel Podestá Junior, Fernando Paladini.
 * BOOOS.h
 *
 *  Created on: Aug 14, 2014
 */
#ifndef QUEUE_CC_
#define QUEUE_CC_
#include "Queue.h"
#include <iostream>
#include <cstdlib>

namespace BOOOS {

    Queue::Queue() {
        _head.next(0);
        _head.prev(0);
        _length = 0;
    }

    Queue::~Queue() {
        while(this->_length != 0)
            this->remove();
    }

    void Queue::insert(Element * elem) {
        if (elem == 0) {
            throw -2;
        }
        if (_length > 0) {
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
            elem->prev(elem); // antes estava next aqui
        }
        _length++;
    }

    // Temp.
    void Queue::insert_ordered(Element * elem) {
        if (elem == 0) {
            throw -2;
        }
        if (_length > 0) {
            Element* temp = _head.next();
            int count = 0;

            while(count < _length) {
                if (elem->rank() >= temp->rank()) {
                    temp = temp->next();
                } else {
                    break;
                }
                count++;
            }

            temp = temp->prev();
            elem->next(temp->next());
            elem->prev(temp);
            temp->next()->prev(elem);
            temp->next(elem);

            if(count == _length) {
                _head.prev(elem);
            }
            if(count == 0) {
                _head.next(elem);
            }
            _length++;

        } else {
            insert(elem);
        }
    }

    Queue::Element * Queue::remove() {
        if (_length == 0) {
            throw -1; 
        }
        Element *originalHead = _head.next();
        Element *last = _head.prev();
        _head.next(originalHead->next());
        _head.next()->prev(last);
        last->next(_head.next());
        _length--;
        return originalHead; 

    }


    void Queue::remove(Element * elem) {
        if (_length == 0) {
            throw -1;
        } 
        if (elem == 0) {
            throw -2;
        }

        Element* temp = _head.next();
        int count = 0;

        while (count < _length) {
            if (elem == temp) {
                break;
            } else {
                temp = temp->next();
            }
            count++;
        }

        if (count == _length) {
            throw -3;
        }

        temp->prev()->next(temp->next());
        temp->next()->prev(temp->prev());

        if(count == 0) {
            _head.next(temp->next());
        } else if(count == _length -1) {
            _head.prev(temp->prev());
        }


        _length--;

    }

    // Private
    Queue::Element * Queue::search(Element * elem) {
        if (_length == 0) {
            throw -1;
        }
        if (elem == 0) {
            throw -2;
        }

        Element* temp = _head.next();
        int count = 0;

        while (count < _length) {
            if (elem == temp) {
                return temp;
            } else {
                temp = temp->next();
            }
            count++;
        }

        throw -3;
    }
    bool Queue::searchB(Element * elem) {
        try {
            Element* e = search(elem);
        } catch (int e) {
            return false;
        }

        return true;
    }

}
#endif