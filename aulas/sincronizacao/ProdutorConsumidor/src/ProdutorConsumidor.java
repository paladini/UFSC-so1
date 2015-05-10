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
    
    
    class Produtor extends Thread {
        Produtor(int num) {_num=num; System.out.println("Produtor "+_num+" criado");}
        public void run() {
            for(int i=0; i<10; i++) {
                //produtor faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                //produtor quer produzir

                //produtor produz
                System.out.println("Produtor "+_num+" come�a a produzir o valor "+i+"...");
                valor[(posicaoProduzir++)%TAM_VETOR] = i;
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                System.out.println("... Produtor "+_num+" termina de produzir");
                
                //termina de produzir

                
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
                
                //consumidor quer consumir

                        
                //consumidor consome
				consumido = valor[(posicaoConsumir++)%TAM_VETOR];
                System.out.println("Consumidor "+_num+" come�a a consumir o valor "+consumido+"...");
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                System.out.println("... Consumidor "+_num+" termina de consumir");
                
                //termina de consumir

            }
        }
        private int _num;
    }
    
    public ProdutorConsumidor() {
        int numConsumidores = 1;//(int)(Math.random()*30) +5;
        int numProdutores = 1;//(int)(Math.random()*30) +5;

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
