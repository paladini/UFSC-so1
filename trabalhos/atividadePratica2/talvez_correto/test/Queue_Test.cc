/*
 * BOOOS.h
 *
 *  Created on: Aug 14, 2014
 */

#include <iostream>
#include <Queue.h>
#include "test_scaffold.h"


using namespace std;
using namespace BOOOS;

class MyElement : public Queue::Element {
public:
	MyElement(string str) : _name(str) {}

	virtual ~MyElement() {}

	string & name() { return _name; }

private:
	string _name;
};

/*
	 Init of methods created by @paladini.
*/
int test_remotion_by_element() {
	Queue q;
	MyElement* person1 = new MyElement("JoÃƒÂ£o");
	MyElement* person2 = new MyElement("Pedro");
	MyElement* person3 = new MyElement("Augusto");
	MyElement* person4 = new MyElement("FÃƒÂ¡bio");

	q.insert(person1);
	q.insert(person2);
	q.insert(person3);
	q.insert(person4);
	q.remove(person3);

	ASSERT(q.head()->next()->next()->next() == person4, 1);
	ASSERT(q.head()->prev()->prev() == person2, 2);
	ASSERT(q.head()->prev() == person4, 3);
	ASSERT(q.head()->next() == person1, 4);
	ASSERT(q.head()->next()->next() == person2, 5);

	q.remove(person2);
	
	ASSERT(q.head()->next()->next() == person4, 6);
	ASSERT(q.head()->next() == person1, 7);
	ASSERT(q.head()->prev() == person4, 8);

	q.remove(person4);

	ASSERT(q.head()->prev() == person1, 9);
	ASSERT(q.head()->next() == person1, 10);

	return 0;
}

int test_ordered_insertion() {
	Queue q;

	Queue::Element* e1 = new Queue::Element();
	Queue::Element* e2 = new Queue::Element();
	Queue::Element* e3 = new Queue::Element();
	Queue::Element* e4 = new Queue::Element();
	e1->rank(1);
	e2->rank(2);
	e3->rank(3);
	e4->rank(4);

	q.insert_ordered(e4);
	q.insert_ordered(e2);
	q.insert_ordered(e3);
	q.insert_ordered(e1);

	/* std::cout << "Next(): " << std::endl;
	std::cout << "e1: " << q.head()->next()->rank() << std::endl;
	std::cout << "e2: " << q.head()->next()->next()->rank() << std::endl;
	std::cout << "e3: " << q.head()->next()->next()->next()->rank() << std::endl;
	std::cout << "e4: " << q.head()->next()->next()->next()->next()->rank() << std::endl;

	std::cout << "Prev(): " << std::endl;
	std::cout << "e1: " << q.head()->prev()->prev()->prev()->prev()->rank() << std::endl;
	std::cout << "e2: " << q.head()->prev()->prev()->prev()->rank() << std::endl;
	std::cout << "e3: " << q.head()->prev()->prev()->rank() << std::endl;
	std::cout << "e4: " << q.head()->prev()->rank() << std::endl;
	
	bool test = q.head()->next()->rank() == q.head()->next()->next()->next()->rank();
	std::cout << "e1 == e3: " << test << std::endl; */

	ASSERT(q.head()->next()->rank() == 1, 1);
	ASSERT(q.head()->next()->next()->rank() == 2, 2);
	ASSERT(q.head()->next()->next()->next()->rank() == 3, 3);
	ASSERT(q.head()->next()->next()->next()->next()->rank() == 4, 4);

	return 0;
}

/* 

	END of methods created by @paladini.

*/

void print_queue(Queue & q) {
	cout << "Queue length: " << q.length() << endl;

	if(q.length()) {
		MyElement * elem = dynamic_cast<MyElement *>(q.head()->next());
		do {
			cout << elem->name() << endl;
			elem = dynamic_cast<MyElement *>(elem->next());
		} while (elem != q.head()->next());
	}

	cout << "==============================" << endl;
}

int test_creation_destruction() {
	Queue *q = new Queue();

	ASSERT(q->length() == 0, 1);
	ASSERT(q->head()->next() == 0, 2);
	ASSERT(q->head()->prev() == 0, 3);

	delete q;

	return 0;
}

int test_insertion() {
	Queue q;

	MyElement * person1 = new MyElement("JoÃƒÂ£o");
	MyElement * person2 = new MyElement("Pedro");
	MyElement * person3 = new MyElement("Augusto");
	MyElement * person4 = new MyElement("FÃƒÂ¡bio");

	q.insert(person1);
	q.insert(person2);
	q.insert(person3);
	q.insert(person4);

	ASSERT(q.head()->next() == person1, 1); // head
	ASSERT(q.head()->prev() == person4, 2); // tail

	MyElement * tmp = dynamic_cast<MyElement*>(q.head()->next());
	ASSERT(tmp == person1, 3);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person2, 4);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person3, 5);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person4, 6);

	return 0;
}



int test_remotion() {
	Queue q;

	MyElement * person1 = new MyElement("JoÃƒÂ£o");
	MyElement * person2 = new MyElement("Pedro");
	MyElement * person3 = new MyElement("Augusto");
	MyElement * person4 = new MyElement("FÃƒÂ¡bio");

	q.insert(person1);
	q.insert(person2);
	q.insert(person3);
	q.insert(person4);

	MyElement * removed_person = dynamic_cast<MyElement *>(q.remove());
	ASSERT(person1 == removed_person, 1);
	delete removed_person;

	ASSERT(q.head()->next() == person2, 2);
	ASSERT(person2->prev() == q.head()->prev(), 3);
	ASSERT(q.head()->prev()->next() == person2, 4);

	return 0;
}

int main() {
	cout << "This program will test the class: Queue" << endl;

	UnitTest tests("Queue");

	tests.attach_test(&test_creation_destruction, "Creation and Destruction");
	tests.attach_test(&test_insertion, "Insertion");
	tests.attach_test(&test_remotion, "Remotion");

	// Tests by @paladini.
	tests.attach_test(&test_remotion_by_element, "Remotion by element (@paladini)");

	// nÃƒÂ£o estÃƒÂ¡ funcionando pq nÃƒÂ£o faz sentido ter uma fila circular ordenada.
	tests.attach_test(&test_ordered_insertion, "Ordered insertion (@paladini)"); 

	tests.run();

	return 0;
}
