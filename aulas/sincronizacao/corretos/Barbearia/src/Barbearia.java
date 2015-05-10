

/*
 Uma barbearia tem um barbeiro, uma cadeira de barbeiro e n cadeiras para os clientes esperarem, 
 se houver algum, sentidos. Se n�o houver nenhum cliente presente, o barbeiro senta-se na cadeira 
 e dorme. Quando um cliente chega, ele tem que acordar o barbeiro. Se outros clientes chegarem 
 enquanto o barbeiro estiver cortando o cabelo de um cliente, eles sentam-se (se houver cadeiras 
 vazias) ou saem da barbearia (se todas as cadeiras estiverem cheias). O problema � programar o 
 barbeiro e os clientes sem cair em condi��es de corrida.
 */

import java.util.concurrent.Semaphore;
public class Barbearia {

    private int numCadeirasLivres = 6;
    private int numClientes = 10; /*(int)(Math.random()*30) +5;*/
    Semaphore cadeiras = new Semaphore(1);
    Semaphore msg = new Semaphore(1);
    Semaphore barberRdy = new Semaphore(0);
    Semaphore clientRdy = new Semaphore(0);
    Semaphore[] clients = new Semaphore[numClientes];

    class Cliente extends Thread {
        Cliente(int num) {_num=num; System.out.println("Cliente "+_num+" criado");}       
        public void run() {
            //for(int i=0; i<1; i++) {
            while(true) {
                //cliente faz qualquer coisa

                try{cadeiras.acquire();} catch(InterruptedException e) {}
                if (numCadeirasLivres > 0) {
                    numCadeirasLivres--;
                    cadeiras.release();
                    clientRdy.release();
                    try{barberRdy.acquire();} catch(InterruptedException e) {}
                    //irá dar deadlock se o for for inconsistente com o for do barbeiro.
                    //cliente quer cortar cabelo
                    try{msg.acquire();} catch (InterruptedException e){}
                    System.out.println("Cliente "+_num+" come�a a ter o cabelo cortado");
                    //cliente vai ter cabelo cortado pelo barbairo
                    try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                    //barbeiro termina de cortar o cabelo do cliente
                    System.out.println("... Cliente "+_num+" terminou de ter o cabelo cortado");
                    msg.release();
                    //try{clients[this._num].acquire();} catch (InterruptedException e) {}
                } else {
                    cadeiras.release();
                    //System.out.println("Saindo para dar uma volta!");
                    try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                }
                //cliente sai da barbearia
            }
                
        }
        private int _num;
    }
     
    class Barbeiro extends Thread {
        Barbeiro() {System.out.println("Barbeiro criado");}       
        public void run() {
            //for(int i=0; i<numClientes; i++) {
            while(true) {
                //barbeiro
                //barbeiro pronto para cortar cabelo de algum cliente
                try {clientRdy.acquire();} catch (InterruptedException e){}
                //irá dar deadlock se o for for inconsistente.
                try{cadeiras.acquire();} catch (InterruptedException e){}
                if (numCadeirasLivres < 6) {
                    numCadeirasLivres++;
                    cadeiras.release();
                    barberRdy.release();
                    //barbeiro vai comecar a cortar cabelo
                    try {msg.acquire();} catch (InterruptedException e) {}
                    System.out.println("barbeiro começa a cortar o cabelo do cliente");
                    try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                    //barbeiro termina de cortar o cabelo do cliente
                    System.out.println("... Barbeiro termina de cortar o cabelo co cliente");
                    msg.release();
                    //clients[i].release();
                    //barbeiro vai descansar
                } else {
                    cadeiras.release();
                    System.out.println("Barbeiro descansou!");
                    try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}

                }
            }
        }
        private int _num;
    }
    
    
    public Barbearia() {
        // int numClientes = (int)(Math.random()*30) +5;
         
        System.out.println("Criando "+numClientes+" clientes");
        Cliente[] cliente = new Cliente[numClientes];

        Barbeiro barbeiro = new Barbeiro();
        barbeiro.start();
        for (int i=0; i<numClientes; i++) {
            cliente[i] = new Cliente(i);
            clients[i] = new Semaphore(0);
        }
        for (int i=0; i<numClientes; i++) cliente[i].start();
        //try{barbeiro.join();} catch (Exception e){}

        //for (int i = 0; i < numClientes; i++) {
        //    try{cliente[i].join();} catch (Exception e){}
        //}
    }
    
    public static void main(String[] args) {
        Barbearia b = new Barbearia();
        //System.out.println("Acabou!");
    }
    
}
