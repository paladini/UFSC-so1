
/*
 Um problema de comunica��o de processos, nada ortodoxo, � o problema da brincadeira das crian�as. 
 Imagine 7 crian�as, que est�o, a princ�pio, quietas. Quatro delas inicialmente possuem uma bola e 
 as outras tr�s, n�o. De repente, sentem vontade de brincar com uma bola. Com esse desejo incontrol�vel, 
 as que j� est�o com a bola simplesmente brincam. As que n�o t�m bola, correm ao cesto de bolas, que 
 est� inicialmente vazio e que suporta, na verdade apenas uma �nica bola. Se o cesto estiver cheio, 
 uma crian�a pega a bola e vai brincar feliz. Se o cesto estiver vazio, ela fica esperando at� outra 
 crian�a coloque uma bola no cesto. Quando uma crian�a termina de brincar, ela tem que colocar a bola 
 no cesto, mas se o cesto j� estiver cheio, ela segura a bola at� que outra crian�a retire a bola que 
 j� est� no cesto, e ent�o solta sua bola no cesto e volta a ficar quieta. Modele esse problema resolvendo 
 os conflitos entre os processos �crian�a�.
 */ 

import java.util.concurrent.Semaphore;

public class BrincadeiraCriancas {
    
    boolean temBola[] = {true, true, true, true, false, false, false};
    
    class Crianca extends Thread {
        Crianca(int num) {_num=num; System.out.println("Crianca "+_num+" criada");}
        public void run() {
            for(int i=0; i<10; i++) {
                //crianca faz qualquer coisa
                try{Thread.sleep((int)Math.random()*400);}catch(Exception e){}
                
                // criança quer brincar com a bola
                
                
                //crianca brinca com a bola
                System.out.println("Crianca "+_num+" come�a a brincar...");
                try{Thread.sleep((int)Math.random()*400);}catch(Exception e){}
                System.out.println("... Crianca "+_num+" termina de brincar");
                
                //termina de brincar e solta a bola
                
            }
        }
        private int _num;
    }
    
    
    public BrincadeiraCriancas() {
        Crianca[] crianca = new Crianca[7];

        for (int i=0; i<7; i++) crianca[i] = new Crianca(i);
        for (int i=0; i<7; i++) crianca[i].start();
    }
    
    public static void main(String[] args) {
        BrincadeiraCriancas bc = new BrincadeiraCriancas();
    }
    
}
