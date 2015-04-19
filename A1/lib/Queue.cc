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


// Queue constructor: must initialize queue's attributes
	Queue::Queue() { _length = 0;}

// Queue destructor: must finalize queue's attributes
	Queue::~Queue() {}


// insert method: must insert the Element at the end of the queue
// Error messages:
//   01: invalid Element (if elem == 0)
//   02: duplicated Element (if elem already is on the queue)
	void Queue::insert(Element * elem) {
		if (elem == 0) {
			throw -2;
		}
		// if (elem == search(elem)) {
		// 	throw -3;
		// }
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

// remove: must search and remove the element from the queue
// Error messages:
//   01: queue is empty
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

	// Queue::Element* Queue::search(Queue::Element* elem) {
	// 	Element* actual = _head.next;
	// 	for (int i = 0; i < _length; i++) {
	// 		if (elem == *actual) {
	// 			return actual;
	// 		}
	// 	}
	// 	actual = actual.next;
	// 	throw -4; /* Doesn't have the element*/
	// }

}
#endif