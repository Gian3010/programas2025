import java.util.*;

enum Status { PENDENTE, EM_ANDAMENTO, CONCLUIDA }

class Tarefa {
    private static int contador = 1;
    private final int id;
    private String descricao;
    private Status status;

    public Tarefa(String descricao) {
        this.id = contador++;
        this.descricao = descricao;
        this.status = Status.PENDENTE;
    }

    public void atualizarStatus(Status novoStatus) {
        this.status = novoStatus;
    }

    @Override
    public String toString() {
        return "Tarefa #" + id + ": " + descricao + " [" + status + "]";
    }
}

public class GerenciadorTarefas {
    private final List<Tarefa> tarefas = new ArrayList<>();
    private final Scanner scanner = new Scanner(System.in);

    public void iniciar() {
        while (true) {
            System.out.println("\n1. Adicionar | 2. Listar | 3. Atualizar | 4. Sair");
            switch (scanner.nextInt()) {
                case 1 -> adicionar();
                case 2 -> listar();
                case 3 -> atualizar();
                case 4 -> System.exit(0);
            }
        }
    }

    private void adicionar() {
        scanner.nextLine();
        System.out.print("Descrição: ");
        tarefas.add(new Tarefa(scanner.nextLine()));
    }

    private void listar() {
        tarefas.forEach(System.out::println);
    }

    private void atualizar() {
        listar();
        System.out.print("ID da tarefa para atualizar: ");
        int id = scanner.nextInt();
        System.out.println("1. PENDENTE | 2. EM ANDAMENTO | 3. CONCLUÍDA");
        int statusIdx = scanner.nextInt();
        tarefas.get(id - 1).atualizarStatus(Status.values()[statusIdx - 1]);
    }

    public static void main(String[] args) {
        new GerenciadorTarefas().iniciar();
    }
}
