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
    private Semaphore lock = new Semaphore(1);
    private Semaphore controleRemoto = new Semaphore(1);
    private Semaphore esperando = new Semaphore(1);
    
    class Paciente extends Thread {
        Paciente(int num) {
            _num=num; 
            _canalFavorito = (int)(Math.random()*4)+1;
            _mudouCanal = false;
            System.out.println("Louco "+_num+" criado com canal favorito "+_canalFavorito);
        }
        
        public void run() {
            for(int i=0; i<100; i++) {

                // Louco faz qualquer coisa
                try{Thread.sleep((int)Math.random()*200);}catch(Exception e){}

                /* O while é necessário pois quando o CR for pego, é necessário que os demais
                 * loucos verifiquem se esse é o canal preferido deles.
                 * "(...) e então TODOS os outros pacientes que gostam desse mesmo canal e 
                 * quiserem assistir televisão, podem assistir junto".
                 *
                 * A outra opção era utilizar um "i--", que julguei pior que essa.
                 */
                try{lock.acquire();}catch(InterruptedException e){}
                while(canalTV != _canalFavorito) {
                    lock.release();

                    // Só um paciente pode tentar adquirir o CR, o resto fica aguardando.
                    // Vai ficar preso aqui, por isso não tem espera ocupada no "while".
                    try{esperando.acquire();}catch(InterruptedException e){}
                    try{lock.acquire();}catch(InterruptedException e){}
                    if (assistindo == 0){
                        lock.release();
                        try{controleRemoto.acquire();}catch(InterruptedException e){} // tenta pegar o CR.
                        _mudouCanal = true;
                        try{lock.acquire();}catch(InterruptedException e){} // agora já pegou o CR.
                        canalTV = _canalFavorito;
                        assistindo++;
                        System.out.println("Louco " +_num+" pega o controle remoto e coloca no canal "+canalTV+"...");
                    }

                    lock.release();
                    esperando.release();
                    try{lock.acquire();}catch(InterruptedException e){} // precisa adquirir o lock de "canalTV" (condição do while)
                }
                lock.release();    
                
                if (!_mudouCanal) {
                    try{lock.acquire();}catch(InterruptedException e){}
                    assistindo++;
                    lock.release();
                } else {
                    _mudouCanal = false;
                }

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
                    System.out.println("Louco " +_num+" solta o controle remoto.");
                    controleRemoto.release();
                }
                lock.release();
                
            }
        }
        private int _num;
        private int _canalFavorito;
        private boolean _mudouCanal;
    }
    
    
    public ControleRemotoLoucos() {
        int numLoucos = 64;
         
        System.out.println("Criando "+numLoucos+" loucos");
        Paciente[] louco = new Paciente[numLoucos];

        for (int i=0; i<numLoucos; i++) louco[i] = new Paciente(i);
        for (int i=0; i<numLoucos; i++) louco[i].start();
    }
    
    public static void main(String[] args) {
        ControleRemotoLoucos crl = new ControleRemotoLoucos();
    }
    
}
