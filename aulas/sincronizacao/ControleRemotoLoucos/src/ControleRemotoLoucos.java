/*
 1)Seja o problema do controle remoto: Num hosp�cio h� apenas uma televis�o que pega 4 canais. 
 Os pacientes apenas descansam ou ent�o assistem televis�o, mas cada paciente tem um canal preferido
 e s� assiste televis�o nesse canal. O paciente que tiver o controle remoto pode escolher o canal 
 de sua prefer�ncia, e ent�o todos os outros pacientes que gostam desse mesmo canal e quiserem 
 assistir televis�o, podem assistir junto. Os que preferem outros canais, ficam esperando. Apenas 
 quando o �ltimo paciente que est� assistindo televis�o em determinado canal sai e vai descansar, 
 � que o controle remoto fica livre, e algum paciente pode escolher outro canal. Modele os n 
 processos "paciente".
 */

import java.util.concurrent.Semaphore;

public class ControleRemotoLoucos {
    
    private int canalTV = 0;
    
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
                
                //louco quer ver televisao no seu canal preferido
                
                //louco ve televisao
                System.out.println("Louco "+_num+" comeca a ver televisao no canal "+canalTV+"...");
                try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
                System.out.println("... Louco "+_num+" termina de ver televisao no canal "+canalTV);
                
                //termina de ver televisao. 
                //Se ningu�m quer ver aquele canal, solta controle remoto
                
            }
        }
        private int _num;
        private int _canalFavorito;
    }
    
    
    public ControleRemotoLoucos() {
        int numLoucos = (int)(Math.random()*30) +5;
         
        System.out.println("Criando "+numLoucos+" loucos");
        Paciente[] louco = new Paciente[numLoucos];

        for (int i=0; i<numLoucos; i++) louco[i] = new Paciente(i);
        for (int i=0; i<numLoucos; i++) louco[i].start();
    }
    
    public static void main(String[] args) {
        ControleRemotoLoucos crl = new ControleRemotoLoucos();
    }
    
}
