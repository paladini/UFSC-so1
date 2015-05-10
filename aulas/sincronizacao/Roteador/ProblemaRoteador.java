/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Roteador;

import java.util.concurrent.Semaphore;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author cancian
 */
public class ProblemaRoteador {   
    private int interfaceRede[] = new int[8];
    
    Semaphore semInterface[] = new Semaphore[8];
    
    class Roteador extends Thread {
        private int id;
        public Roteador(int id) {this.id=id; }
        public void run() {
            int mensagem, interfacedestino;
            for (int i=0; i<10; i++) {
                
                try {semInterface[id].acquire();} catch (InterruptedException ex) {}
                // acessa sua interface de rede
                mensagem = interfaceRede[id];
                semInterface[id].release();
                
                // máscara de rede qualquer
                interfacedestino = (int) (Math.random()*8);

                try {semInterface[interfacedestino].acquire();} catch (InterruptedException ex) {}                
                // acessa a interface destino
                interfaceRede[interfacedestino] = mensagem;
                semInterface[interfacedestino].release();
            }
        }
    }
    
    
    public ProblemaRoteador() {
        for (int i=0; i<8; i++) {
            semInterface[i] = new Semaphore(1);
        }
        
        Roteador[] roteador = new Roteador[8];        
        for (int i=0; i<8; i++) {
            roteador[i] = new Roteador(i);
        }
        for (int i=0; i<8; i++) {
            roteador[i].start();
        }
        
    }
    
    public static void main(String[] args) {
        ProblemaRoteador pr = new ProblemaRoteador();
    }
    
    
}
