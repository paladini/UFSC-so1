#include "Queue.h"
#include <iostream>
using namespace std;

namespace BOOOS {

    // Queue constructor: must initialize queue's attributes

    Queue::Queue() {
        this->_length = 0;
    }

    // Queue destructor: must finalize queue's attributes

    Queue::~Queue() {

    }

    // remove: must search and remove the element from the queue
    // Error messages:
    //   01: queue is empty

    Queue::Element * Queue::remove() {
        Element * aux;

        if (this->_length == 0) return 0;
        else {
            aux = this->getItem(0);
            this->removeItem(aux);
            aux->next(0);
            aux->prev(0);
            return aux;
        }
    }

    void Queue::removeItem(Queue::Element * item) {
        Element * aux = this->head()->next();
        Element * aux2;
        int pos = 0;

        while (aux != item) {
            if (aux->next() == 0) return;
            aux = aux->next();
            pos++;
        }
        if (pos == 0) {
            if (this->_length == 1) {
                this->head()->next(0);
                this->head()->prev(0);
                this->_length--;
            } else {
                aux = this->head()->next()->next();
                this->head()->next(aux);
                aux->prev(this->head()->prev());
                this->head()->prev()->next(aux);
                this->_length--;
            }
        } else {
            if (pos == this->_length) {
                aux = item->prev();
                this->head()->prev(aux);
                aux->next(this->head()->next());
                this->_length--;
            } else {
                aux2 = item->next();
                aux = item->prev();
                aux->next(aux2);
                aux2->prev(aux);
                this->_length--;
            }
        }
    }

    Queue::Element * Queue::imprime() {


    }

    // insert method: must insert the Element at the end of the queue
    // Error messages:
    //   01: invalid Element (if elem == 0)
    //   02: duplicated Element (if elem already is on the queue)

    void Queue::insert(Queue::Element * elem) {
        Element * aux;
        if (this->_length == 0) {
            this->head()->next(elem);
            this->head()->prev(elem);
            elem->next(elem);
            elem->prev(elem);
            this->_length++;
        } else {
            aux = this->head()->prev(); //salvando o valor do ultimo
            elem->prev(aux); //anterior do novo aponta para o último
            aux->next(elem); //proximo ultimo aponta para novo
            this->head()->prev(elem); //atualizando o ultimo
            elem->next(this->head()->next()); //novo ultimo aponta para o primeiro
            this->head()->next()->prev(elem);
            this->_length++;
        }
    }

    void Queue::insereComeco(Element * elem) {
        Element * aux;

        if (this->_length == 0) {
            this->insert(elem);
            return;
        }
        aux = this->head()->next();
        elem->next(aux);
        aux->prev(elem);
        this->head()->next(elem);
        elem->prev(this->head()->prev());
        this->head()->prev()->next(elem);
        this->_length++;
        return;
    }

    void Queue::insereNaPosicao(Element * elem, int posicao) {
        Element * mudar, * aux;
        int pos = 1;

        if (posicao == 1) {
            this->insereComeco(elem);
            return;
        }
        mudar = this->head()->next();
        do {
            mudar = mudar->next();
            pos++;
        } while (pos != posicao);
        if ((posicao == this->_length) && (mudar->rank() < elem->rank())) {
            this->insert(elem);
            return;
        }
        aux = mudar->prev();
        mudar->prev()->next(elem);
        elem->prev(aux);
        mudar->prev(elem);
        elem->next(mudar);
        this->_length++;
    }

    void Queue::insert_ordered(Queue::Element * elem) {
        Element * aux;
        int pos = 1;

        if (this->_length == 0) {
            this->insert(elem);
            return;
        }

        if (this->_length == 1) {
            if (this->head()->next()->rank() < elem->rank()) {
                this->insert(elem);
                return;
            } else {
                this->insereComeco(elem);
                return;
            }
        }

        aux = this->head()->next();
        do {
            if (aux->rank() > elem->rank()) {
                this->insereNaPosicao(elem, pos);
                return;
            }
            aux = aux->next();
            pos++;
        } while (aux != this->head()->prev());
        //insere na posiç�o
        this->insereNaPosicao(elem, pos);

    }

    Queue::Element * Queue::getItem(int pos) {
        int cont = 0;
        Element* aux = this->head()->next();

        if (pos != 0) {
            while (cont = !pos) {
                aux = aux->next();
                cont++;
            }
        }
        return aux;
    }

}
