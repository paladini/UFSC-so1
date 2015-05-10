/*
 Seja o problema dos leitores e escritores: dado um recurso compartilhado, pode haver in�meras 
 tarefas leitoras de seu valor, por�m apenas uma escritora (que altere seu valor). Significa que,
 uma vez um leitor conseguindo acesso ao recurso, outros leitores podem tamb�m acess�-lo, por�m 
 se um escritor conseguir o acesso, nenhum outra tarefa pode faz�-lo. Resolva este problema usando 
 sem�foros, e imaginando que as tarefas leitoras e escritoras, num la�o infinito, tentem acessar 
 periodicamente o recurso. Que tipo de situa��o este problema cl�ssico representa? Implemente-o de 
 forma paralela, escrevendo os processos �Leitor� e �Escritor�.
 */ 

import java.util.concurrent.Semaphore;

public class LeitoresEscritores {
    
    class Escritor extends Thread {
        Escritor(int num) {_num=num; System.out.println("Escritor "+_num+" criado");}
        public void run() {
            for(int i=0; i<10; i++) {
                //escritor faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                //escritor quer acessar banco de dados
                
                //escritor acessa banco de dados
                System.out.println("Escritor "+_num+" come�a a escrever no banco...");
                try{Thread.sleep(100);}catch(Exception e){}
                System.out.println("... Escritor "+_num+" termina de escrever no banco");
                
                //termina de acessar o banco

            }
        }
        private int _num;
    }
    
    class Leitor extends Thread {
        Leitor(int num) {_num=num; System.out.println("Leitor "+_num+" criado");}
        public void run() {
            for (int i=0; i<10; i++) {
                //leitor faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                //leitor quer acessar banco de dados
                
                //leitor acessa banco de dados
                System.out.println("Leitor "+_num+" come�a a ler do banco...");
                try{Thread.sleep(100);}catch(Exception e){}
                System.out.println("... Leitor "+_num+" termina de ler do banco");
                
                //termina de acessar o banco

            }
        }
        private int _num;
    }
    
    public LeitoresEscritores() {
        int numLeitores = (int)(Math.random()*30) +5;
        int numEscritores = (int)(Math.random()*30) +5;
        
        System.out.println("Criando "+numLeitores+" leitores e "+numEscritores+" escritores");
        
        Leitor[] leitor = new Leitor[numLeitores];
        Escritor[] escritor = new Escritor[numEscritores];

        for (int i=0; i<numLeitores; i++) leitor[i] = new Leitor(i);
        for (int i=0; i<numEscritores; i++) escritor[i] = new Escritor(i);
        for (int i=0; i<numLeitores; i++) leitor[i].start();
        for (int i=0; i<numEscritores; i++) escritor[i].start();
    }
    
    public static void main(String[] args) {
        LeitoresEscritores length= new LeitoresEscritores();
    }
    
}
