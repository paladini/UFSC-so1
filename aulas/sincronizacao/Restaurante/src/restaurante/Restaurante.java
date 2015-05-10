/*
 */

package restaurante;

import java.util.concurrent.Semaphore;


public class Restaurante {
    
    class Cliente extends Thread {
        Cliente(int num) {_num=num; System.out.println("Escritor "+_num+" criado");}
        public void run() {
            System.out.println("Cliente "+_num+" quer uma mesa");
            System.out.println("Cliente "+_num+" quer fazer um pedido");
            System.out.println("Cliente "+_num+" faz o pedido");
            System.out.println("Cliente "+_num+" espera pela comida");
            System.out.println("Cliente "+_num+" comendo");
            System.out.println("Cliente "+_num+" quer pedir a conta");
            System.out.println("Cliente "+_num+" espera pela conta");
            System.out.println("Cliente "+_num+" paga");
            System.out.println("Cliente "+_num+" vai embora");
        }
        private int _num;
    }
    
    class Garcon extends Thread {
        Garcon(int num) {_num=num; System.out.println("Garcon "+_num+" criado");}
        public void run() {
            for (int i=0; i<10; i++) {
                System.out.println("garçon "+_num+" espera um cliente");
                System.out.println("garçon "+_num+" pega o pedido do cliente");
                System.out.println("garçon "+_num+" entrega o pedido ao cozinheiro");
                System.out.println("garçon "+_num+" espera a comida ficar pronta");
                System.out.println("garçon "+_num+" entrega a comida para o cliente");
                System.out.println("garçon "+_num+" espera o cliente pedir a conta");
                System.out.println("garçon "+_num+" pede a conta ao atendente");
                System.out.println("garçon "+_num+" espera o atendente calcular a conta");
                System.out.println("garçon "+_num+" leva a conta até o cliente");
                System.out.println("garçon "+_num+" espera o cliente pagar");
                System.out.println("garçon "+_num+" leva o dinheito até o atendente");
            }
        }
        private int _num;
    }
    
    class Cozinheiro extends Thread {
        Cozinheiro(int num) {_num=num; System.out.println("Cozinheiro "+_num+" criado");}
        public void run() {
            for (int i=0; i<10; i++) {
                System.out.println("Cozinheiro "+_num+" espera um pedido");
                System.out.println("Cozinheiro "+_num+" prepara a comida");
                System.out.println("Cozinheiro "+_num+" entrega a comida ao garçon");
            }
        }
        private int _num;
    }
    
    class Atendente extends Thread {
        Atendente(int num) {_num=num; System.out.println("Atendente "+_num+" criado");}
        public void run() {
            for (int i=0; i<10; i++) {
                System.out.println("Atendente "+_num+" espera o pedido de conta");
                System.out.println("Atendente "+_num+" calcula a conta");
                System.out.println("Atendente "+_num+" entrega a conta ao garçon");
                System.out.println("Atendente "+_num+" espera o dinheiro do cliente");
                System.out.println("Atendente "+_num+" encerra a mesa");
            }
        }
        private int _num;
    }
    
    public Restaurante() {
        int numClientes = 10;
        int numGarcons = 2;
        int numCozinheiros = 1;
        int numAtendentes = 2;
        int numMesas = 5;

		System.out.println("Criando clientes e funcionários");
       
        Cliente[] cliente = new Cliente[numClientes];
        Garcon[] garcon = new Garcon[numGarcons];
        Cozinheiro[] cozinheiro = new Cozinheiro[numCozinheiros];
        Atendente[] atendente = new Atendente[numAtendentes];

        for (int i=0; i<numClientes; i++) cliente[i] = new Cliente(i);
        for (int i=0; i<numGarcons; i++) garcon[i] = new Garcon(i);
        for (int i=0; i<numCozinheiros; i++) cozinheiro[i] = new Cozinheiro(i);
        for (int i=0; i<numAtendentes; i++) atendente[i] = new Atendente(i);
        
        for (int i=0; i<numGarcons; i++) garcon[i].start();
        for (int i=0; i<numCozinheiros; i++) cozinheiro[i].start();
        for (int i=0; i<numAtendentes; i++) atendente[i].start();
        for (int i=0; i<numClientes; i++) cliente[i].start();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Restaurante r = new Restaurante();
    }

}
