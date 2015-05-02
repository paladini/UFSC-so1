/*
 * Task.h
 *
 *  Created on: Feb 27, 2014
 *      Author: arliones
 */

#ifndef TASK_H_
#define TASK_H_

#include "Queue.h"
#include <ucontext.h>

namespace BOOOS {

    class Task : public Queue::Element {
    public:

        enum State {
            READY,
            WAITING,
            RUNNING,
            FINISHING,
            SCHEDULER
        };

        Task(void (*entry_point)(void *), int nargs, void * arg);
        virtual ~Task();

        int tid() {
            return _tid;
        }

        State state() {
            return _state;
        }

        void pass_to(Task * t, State s = READY);
        void yield();
        void exit(int code);
        void sleep(int t);

        static Task * self() {
            return (Task*) __running;
        }
        static void init();

        static int count();

        int nice() {
            return rank();
        }

        void nice(int p) {
            p = (p > 20 ? 20 : p < -20 ? -20 : p);
            rank(p);
        }

        int cputime() {
            return this->_cputime;
        }

        void cputime(int cputime) {
            this->_cputime = cputime;
            return;
        }

        int activations() {
            return this->_activations;
        }

        void activations(int activations) {
            this->_activations = activations;
            return;
        }

        int response() {
            return _response;
        }

        void response(int response) {
            this->_response = response;
            return;
        }

        int _exit() {
            return this->_codeExit;
        }

        void _exit(int code) {
            this->_codeExit = code;
            return;
        }

        int join(Task* b);

        int coxilo() {
            return _coxilo;
        }

        void coxilo(int t) {
            _coxilo = t;
        }

        void insert_in_ready(Task * task);
        void requestWakeup();

    private:
        static volatile Task * __running;
        static Task * tMain;
        char * _stack;
        int _tid; // task ID
        ucontext_t ctask;
        static volatile int __tid_counter;
        int _cputime;
        int _coxilo;
        int _cpuaux;
        int _codeExit;
        int _response;
    protected:
        int _activations;
        static Queue __ready;
        static Queue __sleep;
        State _state;
        Queue _sleepQueue;
    };

} /* namespace BOOOS */

#endif /* TASK_H_ */
