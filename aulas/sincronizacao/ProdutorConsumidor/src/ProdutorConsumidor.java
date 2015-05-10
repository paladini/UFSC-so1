/*
Este problema, chamado de Produtor-Consumidor (também conhecido como o problema do buffer limitado), consiste em um conjunto de processos que compartilham um mesmo buffer.
Os processos chamados produtores põem informação no buffer. Os processos chamados consumidores retiram informação deste buffer.
*/

import java.util.concurrent.Semaphore;

public class ProdutorConsumidor {
    
    int TAM_VETOR = 1;
    int valor[];
    int posicaoProduzir = 0;
    int posicaoConsumir = 0;
    
    Semaphore cheio = new Semaphore(0);
    Semaphore vazio = new Semaphore(TAM_VETOR);
    Semaphore mutex = new Semaphore(1);
    
    class Produtor extends Thread {
        Produtor(int num) {_num=num; System.out.println("Produtor "+_num+" criado");}
        public void run() {
            for(int i=0; i<10; i++) {
                //produtor faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                try {
                    //produtor quer produzir
                    cheio.release();

                    //produtor produz
                    mutex.acquire();

                    System.out.println("Produtor "+_num+" começa a produzir o valor "+i+"...");
                    valor[(posicaoProduzir++)%TAM_VETOR] = i;
                    try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                    System.out.println("... Produtor "+_num+" termina de produzir");

                    mutex.release();
                    
                    //termina de produzir
                    vazio.acquire();
                } catch (InterruptedException e) {}
                
            }
        }
        private int _num;
    }
    
    class Consumidor extends Thread {
        Consumidor(int num) {_num=num; System.out.println("Consumidor "+_num+" criado");}
        public void run() {
			int consumido;
            for (int i=0; i<10; i++) {
                //faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                try {
                    //consumidor quer consumir
                    cheio.acquire();
                            
                    //consumidor consome
                    mutex.acquire();
    				consumido = valor[(posicaoConsumir++)%TAM_VETOR];
                    System.out.println("Consumidor "+_num+" começa a consumir o valor "+consumido+"...");
                    try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                    System.out.println("... Consumidor "+_num+" termina de consumir");
                    mutex.release();
                    
                    //termina de consumir
                    vazio.release();
                } catch(InterruptedException e) {}

            }
        }
        private int _num;
    }
    
    public ProdutorConsumidor() {
        int numConsumidores = 1;//(int)(Math.random()*30) +5;
        int numProdutores = 1;//(int)(Math.random()*30) +5;

        valor = new int[TAM_VETOR];
		for (int i=0; i<TAM_VETOR; i++) {
			valor[i]=-9999;
		}
        
        System.out.println("Criando "+numProdutores+" produtores  e "+numConsumidores+" consumidores");
        
        Consumidor[] consumidor = new Consumidor[numConsumidores];
        Produtor[] produtor = new Produtor[numProdutores];

        for (int i=0; i<numConsumidores; i++) consumidor[i] = new Consumidor(i);
        for (int i=0; i<numProdutores; i++) produtor[i] = new Produtor(i);
        for (int i=0; i<numConsumidores; i++) consumidor[i].start();
        for (int i=0; i<numProdutores; i++) produtor[i].start();
    }
    
    public static void main(String[] args) {
        ProdutorConsumidor pc = new ProdutorConsumidor();
    }
    
}
