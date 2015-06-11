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
    
    private int canalTV = -1;
    private int assistindo = 0;
    private Semaphore[] canais;
    private Semaphore lock;
    private Semaphore controleRemoto;
    
    class Paciente extends Thread {
        Paciente(int num, int numCanais) {
            _num=num; 
            _canalFavorito = (int)(Math.random()*numCanais)+1;
            System.out.println("Louco "+_num+" criado com canal favorito "+_canalFavorito);
        }
        
        public void run() {
            for(int i=0; i<100; i++) {

                // Louco faz qualquer coisa
                try{Thread.sleep((int)Math.random()*200);}catch(Exception e){}

                // Só um louco de cada canal passa por vez.
                try{canais[_canalFavorito-1].acquire();}catch(InterruptedException e){}
                try{lock.acquire();}catch(InterruptedException e){}
                if (canalTV != _canalFavorito) {
                    lock.release();

                    // Esperar p/ pegar o CR.
                    try{controleRemoto.acquire();}catch(InterruptedException e){}
                    
                    // Pegou o CR.
                    try{lock.acquire();}catch(InterruptedException e){}
                    canalTV = _canalFavorito;
                    System.out.println("Louco " +_num+" pega o controle remoto e coloca no canal "+canalTV+"...");
                }

                assistindo++;
                lock.release();
                canais[_canalFavorito-1].release();

                // Louco vê televisão.
                System.out.println("\tLouco "+_num+" comeca a ver televisao no canal "+canalTV+"...");
                try{Thread.sleep((int)Math.random()*200);}catch(Exception e){}
                System.out.println("\t... Louco "+_num+" termina de ver televisao no canal "+canalTV);
                
                // Termina de ver televisão. 
                // Se ninguém quer ver aquele canal, solta CR.
                try{lock.acquire();}catch(InterruptedException e){}
                assistindo--;
                if (assistindo == 0) {
                    canalTV = -1;
                    System.out.println("Louco " +_num+" solta o controle remoto.\n");
                    controleRemoto.release();
                }
                lock.release();

            }
        }
        private int _num;
        private int _canalFavorito;
    }
    
    
    public ControleRemotoLoucos() {
        int numLoucos = 64, numeroCanais = 4;
         
        System.out.println("Criando "+numLoucos+" loucos");
        Paciente[] louco = new Paciente[numLoucos];
        canais = new Semaphore[numeroCanais];
        lock = new Semaphore(1);
        controleRemoto = new Semaphore(1);

        for (int i=0; i<numeroCanais; i++) canais[i] = new Semaphore(1);
        for (int i=0; i<numLoucos; i++) louco[i] = new Paciente(i, numeroCanais);
        for (int i=0; i<numLoucos; i++) louco[i].start();  
    }
    
    public static void main(String[] args) {
        ControleRemotoLoucos crl = new ControleRemotoLoucos();
    }
    
}
