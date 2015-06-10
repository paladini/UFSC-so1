/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Ponte;

import java.util.concurrent.Semaphore;

/**
 *
 * @author cancian
 */
public class ProblemaPonte {    
    Semaphore semPonte = new Semaphore(1);
    Semaphore mutexAB = new Semaphore(1);
    Semaphore mutexBA = new Semaphore(1);
    int atravessandoAB = 0;
    int atravessandoBA = 0;
    
    class Pessoa extends Thread {
        private int id;
        public Pessoa(int id) {this.id = id;}
        public void run() {
            for (int i=0; i<10; i++) {

                try{Thread.sleep((long) (Math.random()*100));}catch(InterruptedException e){}
                
                System.out.println("Pessoa "+id+" quer atravessar de A para B");
                try{mutexAB.acquire();} catch(Exception e) {}
                if (atravessandoAB==0) {
                    try{semPonte.acquire();} catch(Exception e) {}
                    System.out.println("Ninguém está atravessando. Começa a atravessar de A para B.");
                }
                atravessandoAB++;
                mutexAB.release();
                // atravessa_ponte_de_A_para_B();
                System.out.println("Pessoa "+id+" atravessando de A para B");
                try{Thread.sleep((long) (Math.random()*100));}catch(InterruptedException e){}
                // terminou de atravessar
                System.out.println("Pessoa "+id+" terminou de atravessar de A para B");
                try{mutexAB.acquire();} catch(Exception e) {}
                atravessandoAB--;
                if (atravessandoAB==0) {
                    System.out.println("Ninguém mais está atravessando de A para B. Libera a ponte.");
                    try{semPonte.release();} catch(Exception e) {}
                }
                mutexAB.release();

                // try{Thread.sleep((long) (Math.random()*100));}catch(InterruptedException e){}

                // System.out.println("Pessoa "+id+" quer atravessar de B para A");
                // try{mutexBA.acquire();} catch(Exception e) {}
                // if (atravessandoBA==0) {
                //     try{semPonte.acquire();} catch(Exception e) {}
                //     System.out.println("Ninguém está atravessando. Começa a atravessar de B para A.");
                // }
                // atravessandoBA++;
                // mutexBA.release();
                // // atravessa_ponte_de_B_para_A();
                // System.out.println("Pessoa "+id+" atravessando de B para A");
                // try{Thread.sleep((long) (Math.random()*100));}catch(InterruptedException e){}
                // // terminou de atravessar
                // System.out.println("Pessoa "+id+" terminou de atravessar de B para A");
                // try{mutexBA.acquire();} catch(Exception e) {}
                // atravessandoBA--;
                // if (atravessandoBA==0) {
                //    System.out.println("Ninguém mais está atravessando de B para A. Libera a ponte.");
                //    try{semPonte.release();} catch(Exception e) {}
                // }
                // mutexBA.release();

            }
            
        }
    }   
    
    public ProblemaPonte() {
        // cria 50 pessoas        
        Pessoa pessoa[] = new Pessoa[50];        
        for (int i=0; i<50; i++) {
            pessoa[i] = new Pessoa(i);
        }
        for (int i=0; i<50; i++) {
            pessoa[i].start();
        }
    }
    
    public static void main(String[] args) {
        ProblemaPonte pp = new ProblemaPonte();
    }
    
    
}