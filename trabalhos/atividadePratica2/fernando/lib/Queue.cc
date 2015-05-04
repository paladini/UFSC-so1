/* Emmanuel PodestÃƒÂ¡ Junior, Fernando Paladini.
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
                if (elem >= temp) {
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
            throw -1; // Fila vazia
        }
        Element *originalHead = _head.next();
        Element *last = _head.prev();
        _head.next(originalHead->next());
        _head.next()->prev(last);
        last->next(_head.next());
        _length--;
        return originalHead; 
        /* if (!_length) {
            throw 1;
        }
        Element* aux = _head.next();
        _head.prev()->next(aux->next());
        _head.next(aux->next());
        _head.next()->prev(_head.prev());
        --_length;
        return aux; */
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

        // Element not found.
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

        delete temp;
        temp = NULL;
        _length--;


        /* Element* temp = _head.next();
        bool exist = true;
        if (temp != e) {
            temp = temp->next();
            while (temp != e) {
                temp = temp->next();
                if (temp == _head.next()) {
                    exist = false;
                }
            }
        }

        if (exist) {
            temp->prev()->next(temp->next());
            temp->next()->prev(temp->prev());
            delete temp;
            temp = NULL;
            _length--; 
        } else {
            throw -3;
        } */
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
                if (temp == _head.next()) {
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
    bool Queue::searchB(Element * elem) {
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
                if (temp == _head.next()) {
                    exist = false;
                }
            }
        }
        return exist;
        // if (exist) {
        //     return temp;
        // } else {
        //     return 0;
        // }
    }

}
#endif