/*
Problema do barbeiro dorminhoco

O problema consiste em simular o funcionamento de uma barbearia que possui as seguintes características.
- A barbearia tem uma sala de espera com N cadeiras, uma cadeira de barbear e um barbeiro dorminhoco.
- Se não existem clientes à espera, o barbeiro senta em uma cadeira e dorme.
- Quando chega um cliente, ele acorda o barbeiro.
- Se chega outro cliente enquanto o barbeiro está trabalhando, ele ou ocupa uma cadeira e espera (se tem
alguma cadeira disponível) ou vai embora (se todas as cadeiras estão ocupadas).
Obs: Barbeiro e clientes são processos, mecanismos de sincronização devem ser utilizados para
simular a situação descrita acima.
*/


import java.util.concurrent.Semaphore;

public class Barreira {
    
    
    
    class Trabalhador extends Thread {
        Trabalhador(int num) {_num=num; System.out.println("Trabalhador "+_num+" criado");}
        public void run() {
            for(int i=0; i<10; i++) {               
                //Trabalhador quer trabalhar

                
                //trabalhador trabalha
                System.out.println("Trabalhador "+_num+" começa a trabalhar...");
                try{Thread.sleep(100);}catch(Exception e){}
                System.out.println("... Trabalhador "+_num+" termina de trabalhar");
                
                //termina de acessar o banco

            }
        }
        private int _num;
    }
    
    class Coordenador extends Thread {
        Coordenador() {System.out.println("Coordenador criado");}
        public void run() {
            for (int i=0; i<10; i++) {
                //coordenador inicia 
                
                //coordenador quer liberar trabalhadores
                System.out.println("Coordenador iniciando o trabalho da iteração " + i);
                
                //coordenador espera trabalhadores terminarem
                
                //coordenador junta o trabalho

            }
        }

        private int _num;
    }
    
    public Barreira() {
        int numTrabalhadores = (int)(Math.random()*10) +10;
        
        System.out.println("Criando "+numTrabalhadores+" trabalhadores");
        
        Trabalhador[] trabalhador = new Trabalhador[numTrabalhadores];

        for (int i=0; i<numTrabalhadores; i++) trabalhador[i] = new Trabalhador(i);
        for (int i=0; i<numTrabalhadores; i++) trabalhador[i].start();
        Coordenador coordenador = new Coordenador();
        coordenador.start();
    }
    
    public static void main(String[] args) {
        Barreira b = new Barreira();
    }
    
}
