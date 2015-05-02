#include "Timer.h"
#include "BOOOS.h"
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>


using namespace std;

namespace BOOOS {

    Timer::Timestamp Timer::__ticks = 0;
    itimerval Timer::__timer;
    struct sigaction Timer::__action;
    Scheduler * Timer::__scheduler;
    Timer::Timestamp Timer::__period;

    void Timer::init(Scheduler * sched, Timestamp period) {
        __ticks = 0;
        __scheduler = sched;
        __period = period;
        // define a ação para o sinal de timer
        __action.sa_handler = sig_handler;

        sigemptyset(&__action.sa_mask);
        __action.sa_flags = 0;
        if (sigaction(SIGALRM, &__action, 0) < 0) {
            perror("Erro em sigaction: ");
            exit(1);
        }
        __timer.it_value.tv_sec = 0; // primeiro disparo, em segundos
        __timer.it_interval.tv_sec = 0; // disparos subsequentes, em segundos
        __timer.it_value.tv_usec = BOOOS_Configuration::TIMER_RESOLUTION;
        __timer.it_interval.tv_usec = BOOOS_Configuration::TIMER_RESOLUTION; // disparos subsequentes, em micro-segundos
        //cout << "Configuracao timer" << endl;
    }

    void Timer::start() {
        // arma o temporizador ITIMER_REAL (vide man setitimer)
        setitimer(ITIMER_REAL, &__timer, 0);
    }

    void Timer::delay_ticks(Timer::Timestamp t) {
        Timestamp start = ticks();
        while (ticks() - start <= t);
    }

    void Timer::delay(Timer::Timestamp t) {
        Timestamp start = time();
        while (time() - start <= t);
    }

    void Timer::sig_handler(int signum) {
        __ticks++;

        if ((__ticks % __period) == 0)
            __scheduler->notify_time(__ticks);
    }

    Timer::Timestamp Timer::ticks() {
        return __ticks;
    }

    Timer::Timestamp Timer::time() {
        return __ticks * BOOOS_Configuration::TIMER_RESOLUTION;
    }
} /* namespace BOOOS */
