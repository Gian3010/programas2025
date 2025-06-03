import random

def jogar_forca():
    print("=== Jogo da Forca ===")
    print("Escolha o nível de dificuldade:")
    print("1. Fácil (8 tentativas, palavra curta)")
    print("2. Médio (6 tentativas, palavra média)")
    print("3. Difícil (4 tentativas, palavra longa)")
    
    # Seleção de dificuldade
    nivel = input("Escolha o nível (1, 2 ou 3): ")
    if nivel == "1":
        palavras = ["casa", "bola", "gato", "rato", "carro"]
        tentativas = 8
    elif nivel == "2":
        palavras = ["escola", "amigo", "viagem", "janela", "pessoa"]
        tentativas = 6
    elif nivel == "3":
        palavras = ["computador", "caminhão", "estudante", "bicicleta", "professor"]
        tentativas = 4
    else:
        print("Nível inválido! Saindo do jogo.")
        return

    # Seleção da palavra
    palavra = random.choice(palavras)
    palavra_mostrada = ["_"] * len(palavra)

    # Lógica do jogo
    print("\nA palavra é:", " ".join(palavra_mostrada))
    letras_tentadas = []

    while tentativas > 0:
        letra = input("\nDigite uma letra: ").lower()
        
        if letra in letras_tentadas:
            print("Você já tentou essa letra.")
            continue
        
        letras_tentadas.append(letra)

        if letra in palavra:
            for i, l in enumerate(palavra):
                if l == letra:
                    palavra_mostrada[i] = letra
            print("Palavra: ", " ".join(palavra_mostrada))
        else:
            tentativas -= 1
            print(f"Letra errada! Tentativas restantes: {tentativas}")
        
        if "_" not in palavra_mostrada:
            print("\nParabéns! Você venceu! A palavra era:", palavra)
            break
    
    print("\nVocê perdeu! A palavra era:", palavra)
    
# Executar o jogo
jogar_forca()
