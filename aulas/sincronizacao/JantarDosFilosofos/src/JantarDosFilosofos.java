/*
 Este problema consiste em cinco fil�sofos est�o sentados em c�rculo, tentando comer espaguete 
 com a ajuda de garfos. Cada fil�sofo possui uma bacia de massa mas h� apenas cinco garfos,
 colocados um a direita e outro a esquerda de cada fil�sofo, para serem compartilhados entre eles. 
 Isto cria um problema, pois ambos os garfos( direita e esquerda ) s�o necess�rios para cada um 
 dos fil�sofos poder comer. As alternativas dos fil�sofos compreendem duas fases: Pensar e Comer. 
 No modo pensar, um fil�sofo n�o segura um garfo. Por�m, quando est� com fome(depois de ficar por
 um tempo finito no modo Pensar) o fil�sofo tenta pegar os dois garfos na direita e esquerda.
 */

import java.util.concurrent.Semaphore;



public class JantarDosFilosofos {

    class Filosofo extends Thread {
       Filosofo(int i){_num=i; System.out.println("Filosofo "+i+" criado.");}    
       public void run() {
           for (int i=0;i<10;i++){
               //faz qualquer coisa
               try{Thread.sleep((int)Math.random()*100);}catch(Exception e){}
               
               //quer comer
               
               //come
               System.out.println("Fil�sofo "+_num+" come�a a comer pela "+i+"a vez...");
               try{Thread.sleep(200);}catch(Exception e){}
               System.out.println("...Fil�sofo "+_num+" termina de comer pela "+i+"a vez");
               
               //termina de comer

           }
       }

       private int _num;
    }
    
    public JantarDosFilosofos() {
        System.out.println("Criando fil�fos");
        
        Filosofo[] filosofo = new Filosofo[5];
       
        for(int i=0;i<5;i++) filosofo[i] = new Filosofo(i);
        for(int i=0;i<5;i++) filosofo[i].start(); 
    }
    
    public static void main(String[] args) {
        JantarDosFilosofos jf = new JantarDosFilosofos();
    }
    
}
