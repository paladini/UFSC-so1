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

public class ControleRemotoLoucos2 {
    
    private int canalTV = -1;
    private int assistindo = 0;
    private Semaphore lock = new Semaphore(1);
    private Semaphore controleRemoto = new Semaphore(1);
    private Semaphore esperando = new Semaphore(1);
    
    class Paciente extends Thread {
        Paciente(int num) {
            _num=num; 
            _canalFavorito = (int)(Math.random()*5)+1;
            System.out.println("Louco "+_num+" criado com canal favorito "+_canalFavorito);
        }
        
        public void run() {
            for(int i=0; i<10; i++) {
                //louco faz qualquer coisa
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                
                // try{lock.acquire();}catch(InterruptedException e){}
                // while(canalTV != _canalFavorito) {
                //     lock.release();
                //     esperando.acquire();
                //     if (assistindo == 0){
                //         controleRemoto.acquire();
                //         canalTV = _canalFavorito;
                //     }
                //     esperando.release();
                //     try{lock.acquire();}catch(InterruptedException e){}
                // }

                while(true) {
                    try{lock.acquire();}catch(InterruptedException e){}
                    if (canalTV != _canalFavorito) {
                        lock.release();

                        // Apenas um paciente pode obter o controle remoto por vez.
                        try{esperando.acquire();}catch(InterruptedException e){}
                        if (assistindo == 0) {
                            try{controleRemoto.acquire();}catch(InterruptedException e){}
                            canalTV = _canalFavorito;
                            System.out.println("Louco " +_num+" pega o controle remoto e coloca no canal "+canalTV+"...");
                        }
                        esperando.release();
                        continue;
                    }
                    assistindo++;
                    lock.release();
                    break;
                }

                // assistindo++;
                // lock.release();

                //louco ve televisao
                System.out.println("\tLouco "+_num+" comeca a ver televisao no canal "+canalTV+"...");
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                System.out.println("\t... Louco "+_num+" termina de ver televisao no canal "+canalTV);
                
                //termina de ver televisao. 
                //Se ningu�m quer ver aquele canal, solta controle remoto
                try{lock.acquire();}catch(InterruptedException e){}
                assistindo--;
                if (assistindo == 0) {
                    canalTV = -1;
                    System.out.println("Louco " +_num+" solta o controle remoto.");
                    controleRemoto.release();
                }
                lock.release();
                
            }
        }
        private int _num;
        private int _canalFavorito;
    }
    
    
    public ControleRemotoLoucos2() {
        int numLoucos = 10;
         
        System.out.println("Criando "+numLoucos+" loucos");
        Paciente[] louco = new Paciente[numLoucos];

        for (int i=0; i<numLoucos; i++) louco[i] = new Paciente(i);
        for (int i=0; i<numLoucos; i++) louco[i].start();
    }
    
    public static void main(String[] args) {
        ControleRemotoLoucos2 crl = new ControleRemotoLoucos2();
    }
    
}
