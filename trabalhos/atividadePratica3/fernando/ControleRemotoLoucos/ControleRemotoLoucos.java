/*
 1)Seja o problema do controle remoto: Num hospício há apenas uma televisão que pega 4 canais. 
 Os pacientes apenas descansam ou então assistem televisão, mas cada paciente tem um canal preferido
 e só assiste televisão nesse canal. O paciente que tiver o controle remoto pode escolher o canal 
 de sua preferência, e então todos os outros pacientes que gostam desse mesmo canal e quiserem 
 assistir televisão, podem assistir junto. Os que preferem outros canais, ficam esperando. Apenas 
 quando o último paciente que está assistindo televisão em determinado canal sai e vai descansar, 
 é que o controle remoto fica livre, e algum paciente pode escolher outro canal. Modele os n 
 processos "paciente".
 */

import java.util.concurrent.Semaphore;

public class ControleRemotoLoucos {
    
    private int canalTV = 0;
    private int assistindo = 0;
    private Semaphore controle = new Semaphore(1);
    private Semaphore lock = new Semaphore(1);
    
    // (a) Descomentar todos os (a) melhora pois ele executa tudo, entretanto fica praticamente "sequencial". 
    // Por ser uma solução meio paliativa, preferi deixar estas linhas comentadas.
    // private Semaphore esperando = new Semaphore(0);
    
    class Paciente extends Thread {
        Paciente(int num) {
            _num=num; 
            _canalFavorito = (int)(Math.random()*5)+1;
            System.out.println("Louco "+_num+" criado com canal favorito "+_canalFavorito);
        }
        
        public void run() {
            for(int i = 0; i < 100; i++) {

                //louco faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                //louco quer ver televisao no seu canal preferido
                try{lock.acquire();} catch(InterruptedException e){}
                if (canalTV == 0 || canalTV == _canalFavorito) {
                    if (assistindo == 0) {
                        canalTV = _canalFavorito;
                    }
                    assistindo++;
                    lock.release();

                    //louco ve televisao
                    try{controle.acquire();}catch(InterruptedException e){}
                    System.out.println("Louco "+_num+" comeca a ver televisao no canal "+canalTV+"...");
                    try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                    System.out.println("... Louco "+_num+" termina de ver televisao no canal "+canalTV);
                    controle.release();
                    
                    //termina de ver televisao. 
                    //Se ninguém quer ver aquele canal, solta controle remoto
                    try{lock.acquire();}catch(InterruptedException e){}
                    assistindo--;
                    if (assistindo == 0) {
                        canalTV = 0;
                    }
                    lock.release();
                    
                    // (a)
                    //esperando.release();
                } else {
                    lock.release();
                    
                    // (a)
                    //try{esperando.acquire();}catch(InterruptedException e){}
                    //i--;
                }
                
            }
        }
        private int _num;
        private int _canalFavorito;
    }
    
    
    public ControleRemotoLoucos() {
        int numLoucos = 64;
         
        System.out.println("Criando " + numLoucos + " loucos");
        Paciente[] louco = new Paciente[numLoucos];

        for (int i=0; i<numLoucos; i++) louco[i] = new Paciente(i);
        for (int i=0; i<numLoucos; i++) louco[i].start();
    }
    
    public static void main(String[] args) {
        ControleRemotoLoucos crl = new ControleRemotoLoucos();
    }
    
}
