import random

def menu():
    print("=== Jogo da Forca ===")
    print("1. Iniciar Jogo")
    print("2. Sair")
    opcao = input("Escolha uma opção: ")
    return opcao

def escolher_dificuldade():
    print("\nEscolha o nível de dificuldade:")
    print("1. Fácil")
    print("2. Médio")
    print("3. Difícil")
    nivel = input("Escolha uma opção: ")
    return nivel

def escolher_palavra(nivel):
    palavras = {
        "1": ["casa", "bola", "gato", "rato", "carro"],
        "2": ["escola", "amigo", "viagem", "janela", "pessoa"],
        "3": ["computador", "caminhão", "estudante", "bicicleta", "professor"]
    }
    return random.choice(palavras[nivel])

def iniciar_jogo():
    while True:
        opcao = menu()
        if opcao == "2":
            print("Obrigado por jogar!")
            break
        elif opcao == "1":
            nivel = escolher_dificuldade()
            if nivel not in ["1", "2", "3"]:
                print("Nível inválido, tente novamente.")
                continue
            
            palavra_secreta = escolher_palavra(nivel)
            tentativas = 8 if nivel == "1" else 6 if nivel == "2" else 4
            letras_reveladas = 1 if nivel == "1" else 0
            
            # Mostrar palavra inicial
            palavra_mostrada = list("_" * len(palavra_secreta))
            for _ in range(letras_reveladas):
                indice = random.choice(range(len(palavra_secreta)))
                palavra_mostrada[indice] = palavra_secreta[indice]

            print("\nA palavra é:", " ".join(palavra_mostrada))
            letras_tentadas = set()

            while tentativas > 0:
                letra = input("\nDigite uma letra: ").lower()
                if letra in letras_tentadas:
                    print("Você já tentou essa letra.")
                    continue
                
                letras_tentadas.add(letra)

                if letra in palavra_secreta:
                    for i, l in enumerate(palavra_secreta):
                        if l == letra:
                            palavra_mostrada[i] = letra
                    print("Boa! A palavra é:", " ".join(palavra_mostrada))
                else:
                    tentativas -= 1
                    print(f"Letra errada! Tentativas restantes: {tentativas}")

                if "_" not in palavra_mostrada:
                    print("\nParabéns! Você venceu!")
                    break
            
            if tentativas == 0:
                print("\nVocê perdeu! A palavra era:", palavra_secreta)
        else:
            print("Opção inválida, tente novamente.")

# Iniciar o programa
iniciar_jogo()
