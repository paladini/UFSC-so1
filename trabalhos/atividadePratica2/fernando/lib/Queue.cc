/* Emmanuel Podestá Junior, Fernando Paladini.
 * BOOOS.h
 *
 *  Created on: Aug 14, 2014
 */
#ifndef QUEUE_CC_
#define QUEUE_CC_
#include "Queue.h"
#include <cstdlib>

namespace BOOOS {

    Queue::Queue() {
        _head.next(0);
        _head.prev(0);
        _length = 0;
    }

    Queue::~Queue() {}

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
            elem->next(elem);
        }
        _length++;
    }

    // to be checked by @EPodesta
    void Queue::insert_ordered(Element * elem) {
        if (elem == 0) {
            throw -2;
        }
        if (_length > 0) {
            Element* temp = _head.next(); // don't know if must be _head->next() or just _head.
            bool exist = true;

            if(temp > elem) {
                temp = temp->next();
                while (temp > elem) {
                    temp = temp->next();
                    if (&temp == &_head.next()) {
                        found = false;
                        break;
                    }
                }
            }            

            // Don't care if temp == elem or temp < elem.
            if (exist) {
                temp = temp->prev();
                elem->next(temp->next());
                elem->prev(temp);
                temp->next()->prev(elem);
                temp->next(elem);
                _length++;
            } 
        } else {
            insert(elem);
        }
    }

    Queue::Element * Queue::remove() {
        if (_length == 0) {
            throw -1; /* Fila vazia */
        }
        Element *originalHead = _head.next();
        Element *last = _head.prev();
        _head.next(originalHead->next());
        _head.next()->prev(last);
        last->next(_head.next());
        _length--;
        return originalHead;
    }


    void Queue::remove(Element * e) {
        if (_length == 0) {
            throw -1;
        } 
        if (e == 0) {
            throw -2;
        }

        Element* temp = _head.next();
        bool exist = true;
        if (temp != e) {
            temp = temp->next();
            while (temp != e) {
                temp = temp->next();
                if (&temp == &_head.next()) {
                    exist = false;
                }
            }
        }

        if (exist) {
            temp->prev()->next(temp->next());
            temp->next()->prev(temp->prev());
            delete temp;
            _length--; 
        } else {
            throw -3;
        }
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
        bool exist = true;
        if (temp != elem) {
            temp = temp->next();
            while (temp != elem) {
                temp = temp->next();
                if (&temp == &_head.next()) {
                    exist = false;
                }
            }
        }

        if (exist) {
            return temp;
        } else {
            return 0;
        }
    }

}
#endif