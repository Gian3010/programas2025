import java.util.concurrent.*;

class Buffer {
    private final Semaphore cheio = new Semaphore(0);
    private final Semaphore vazio = new Semaphore(1);
    private int dado;

    public void produzir(int valor) throws InterruptedException {
        vazio.acquire();
        this.dado = valor;
        System.out.println("Produzido: " + valor);
        cheio.release();
    }

    public int consumir() throws InterruptedException {
        cheio.acquire();
        int valor = this.dado;
        System.out.println("Consumido: " + valor);
        vazio.release();
        return valor;
    }
}

public class ProdutorConsumidor {
    public static void main(String[] args) {
        Buffer buffer = new Buffer();

        Runnable produtor = () -> {
            for (int i = 0; i < 5; i++) {
                try {
                    buffer.produzir(i);
                    Thread.sleep(500);
                } catch (InterruptedException ignored) {}
            }
        };

        Runnable consumidor = () -> {
            for (int i = 0; i < 5; i++) {
                try {
                    buffer.consumir();
                    Thread.sleep(800);
                } catch (InterruptedException ignored) {}
            }
        };

        new Thread(produtor).start();
        new Thread(consumidor).start();
    }
}
    