import java.util.*;
import java.util.stream.*;

class Usuario {
    String nome;
    List<String> interesses;

    Usuario(String nome, List<String> interesses) {
        this.nome = nome;
        this.interesses = interesses;
    }

    public List<String> getInteresses() {
        return interesses;
    }

    public String getNome() {
        return nome;
    }
}

public class Recomendador {
    public static void main(String[] args) {
        List<Usuario> usuarios = List.of(
            new Usuario("Ana", List.of("Java", "IA", "Jogos")),
            new Usuario("Bruno", List.of("Python", "Java", "Dados")),
            new Usuario("Carlos", List.of("C++", "Java", "IA"))
        );

        // Conteúdo popular
        Map<String, Long> interessesPopulares = usuarios.stream()
            .flatMap(u -> u.getInteresses().stream())
            .collect(Collectors.groupingBy(i -> i, Collectors.counting()));

        interessesPopulares.entrySet().stream()
            .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
            .limit(3)
            .forEach(entry -> System.out.println("Tópico: " + entry.getKey() + " - " + entry.getValue() + " usuários"));
    }
}
