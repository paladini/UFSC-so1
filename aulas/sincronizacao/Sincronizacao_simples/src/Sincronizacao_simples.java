

import java.util.concurrent.Semaphore;

public class Sincronizacao_simples {
    
    class Processo extends Thread {
        Processo(int num) {_num=num; System.out.println("Processo "+_num+" criado");}
        public void run() {
            for(int i=0; i<10; i++) {
                //processo faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                //processo quer executar a RC
                
                //RC
                System.out.println("Processo "+_num+" entrou na RC....");
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                System.out.println("... Processo "+_num+" vai sair da RC");
                
                //processo saiu da RC
   
            }
        }
        private int _num;
    }
    
    
    public Sincronizacao_simples() {
        int numProcessos = 10;//(int)(Math.random()*30) +5;
                
        System.out.println("Criando "+numProcessos+" processos");
        
        Processo[] processo = new Processo[numProcessos];

        for (int i=0; i<numProcessos; i++) processo[i] = new Processo(i);
        for (int i=0; i<numProcessos; i++) processo[i].start();
    }
    
    public static void main(String[] args) {
        Sincronizacao_simples ss = new Sincronizacao_simples();
    }
    
}
