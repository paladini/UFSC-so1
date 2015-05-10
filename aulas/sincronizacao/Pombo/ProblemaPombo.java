/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Pombo;

import java.util.concurrent.Semaphore;

/**
 *
 * @author cancian
 */
public class ProblemaPombo {
    private final int N = 5;
    private final int NumUsuarios = 15;
    int contaPostIt=0;
    int terminados=0;
    
    Semaphore mochila = new Semaphore(N);
    Semaphore pomboPodeVoar = new Semaphore(0);
    Semaphore semConta = new Semaphore(1);
    
    class Pombo extends Thread {
        public void run() {
            while (terminados<NumUsuarios) {
                
                System.out.println("Pombo quer voar");
                try{pomboPodeVoar.acquire();} catch(Exception e){}
                try{semConta.acquire();} catch(Exception e) {}

                System.out.println("Pombo leva mochile ate B");
                //leva_mochile_ate_B_e volta();
                try{Thread.sleep((long) (Math.random()*100));}catch(InterruptedException e){}
                contaPostIt = 0;

                semConta.release();
                for (int i=0; i<N; i++) {
                    mochila.release();
                }
                
                System.out.println("Pombo voltou");                
            }            
        }
    }
    
    class Usuario extends Thread {
        private int id;
        public Usuario(int id) {this.id=id;}
        public void run() {
            for (int i=0; i<10; i++) {
                
                try{Thread.sleep((long) (Math.random()*100));}catch(InterruptedException e){}
                
                System.out.println("Usuario "+id+" quer colar mensagem");
                try{mochila.acquire();} catch(Exception e) {}

                try{semConta.acquire();} catch(Exception e) {}
                System.out.println("Usuario "+id+" cola mensagem na mochila");
                //colaPostIt_na_mochila();
                try{Thread.sleep((long) (Math.random()*100));}catch(InterruptedException e){}
                contaPostIt++;
                
                if(contaPostIt==N) {
                    // libera o pombo para voar
                    pomboPodeVoar.release();
                }                
                semConta.release();  

            }            
            terminados++;
        }
    }
    
    public ProblemaPombo() {
        // cria NumUsuarios usuarios
        Usuario usuario[] = new Usuario[NumUsuarios];
        for (int i=0; i<NumUsuarios; i++) {
            usuario[i] = new Usuario(i);
        }
        // cria um pombo
        Pombo pombo = new Pombo();
        
        // coloca todos para executar
        for (int i=0; i<10; i++) {
            usuario[i].start();
        }
        pombo.start();
    }
    
    public static void main(String[] args) {
        ProblemaPombo pp = new ProblemaPombo();
    }
      
}
