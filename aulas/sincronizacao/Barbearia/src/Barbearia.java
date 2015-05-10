

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

    Semaphore sCadeirasLivres = new Semaphore(0); // pode ter 6 clientes por vez
    Semaphore sCadeiraBarbeiro = new Semaphore(0); // pode ter 1 cliente por vez
    Semaphore sDormirCadeira = new Semaphore(0); // controle de barbeiro dormindo / sendo acordado por cliente.
    Semaphore sTemp = new Semaphore(1); // semáfaro binário para testar condições do if.
    
    // Apenas para sincronização das mensagens de "começou a ser atendido", "terminado".
    // Precisou de tudo isso pois aquele sleep tanto em cliente como em barbeiro ferrou tudo.
    Semaphore sMessageBarber = new Semaphore(1);
    Semaphore sMessageClient = new Semaphore(0);
    
    class Cliente extends Thread {
        Cliente(int num) {_num=num; System.out.println("Cliente "+_num+" criado");}       
        public void run() {

            // while (true) {
            for(int i=0; i<10; i++) {
                //cliente faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                //cliente quer cortar cabelo
                try {

                    // Verifica se tem lugar no barbeiro.
                    sTemp.acquire();
                    if (numCadeirasLivres > 0) {

                        numCadeirasLivres--;
                        sTemp.release();

                        // Acorda o barbeiro e senta em uma cadeira vazia.
                        sDormirCadeira.release();
                        System.out.println("Cliente " + _num + " entrou na fila.");
                        sCadeirasLivres.acquire();
                        
                        // Quer ter o cabelo cortado, entra na fila.
                        sCadeiraBarbeiro.acquire();
                    
                        // Está sendo atendido.
                        sMessageClient.acquire();
                        System.out.println(_num+" está sendo atendido.");
                        try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                        System.out.println(_num+" terminou de ser atendido.");
                        sMessageBarber.release();
                        
                        //cliente sai da barbearia
                    } else {
                        sTemp.release();
                    }
                } catch (InterruptedException e) {}
                
            }
        }
        private int _num;
    }
     
    class Barbeiro extends Thread {
        Barbeiro() {System.out.println("Barbeiro criado");}       
        public void run() {
            // while (true) {
            for(int i=0; i<10; i++) {
                //barbeiro
                
                try {
                    if (numCadeirasLivres < 6) {
                        
                        // barbeiro enrola um pouco.
                        try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                    
                        //barbeiro pronto para cortar cabelo de algum cliente
                        
                        //barbeiro vai comecar a cortar cabelo
                        sCadeirasLivres.release();
                        numCadeirasLivres++;
                        sCadeiraBarbeiro.release();

                        // Apenas para fins de sincronização / envio de mensagem por causa desse sleep maldito.
                        sMessageBarber.acquire();
                        System.out.println("Barbeiro começa.");
                        try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                        sMessageClient.release();
                        sMessageBarber.acquire();
                        sMessageBarber.release();

                        //barbeiro termina de cortar o cabelo do cliente
                        System.out.println("Barbeiro termina.");

                    } else {
                        System.out.println("Barbeiro foi pastar (ou dormir).");
                        sDormirCadeira.acquire();
                        System.out.println("Barbeiro foi acordado.");
                    }
                } catch (InterruptedException e) { }

            }
        }
        private int _num;
    }
    
    
    public Barbearia() {
        int numClientes = (int)(Math.random()*30) +5;
         
        System.out.println("Criando "+numClientes+" clientes");
        Cliente[] cliente = new Cliente[numClientes];

        Barbeiro barbeiro = new Barbeiro();
        barbeiro.start();
        for (int i=0; i<numClientes; i++) cliente[i] = new Cliente(i);
        for (int i=0; i<numClientes; i++) cliente[i].start();
    }
    
    public static void main(String[] args) {
        Barbearia b = new Barbearia();
    }
    
}
