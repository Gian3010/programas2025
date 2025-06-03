def fatorial(numero):
    if numero == 0:
        return 1
    else:
        return numero * fatorial(numero - 1)

# Exemplo de uso
numero = int(input("Digite um número: "))
print(f"O fatorial de {numero} é {fatorial(numero)}")




