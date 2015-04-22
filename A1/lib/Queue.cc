/*
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


}
#endif