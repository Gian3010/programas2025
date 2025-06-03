class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class Stack:
    def __init__(self):
        self.top = None

    def push(self, value):
        new_node = Node(value)
        new_node.next = self.top
        self.top = new_node

    def pop(self):
        if self.is_empty():
            raise Exception("Erro: Pilha vazia!")
        value = self.top.value
        self.top = self.top.next
        return value

    def peek(self):
        if self.is_empty():
            raise Exception("Erro: Pilha vazia!")
        return self.top.value

    def is_empty(self):
        return self.top is None

    def to_list(self):
        result = []
        current = self.top
        while current:
            result.append(current.value)
            current = current.next
        return result

    def clear(self):
        self.top = None

    def size(self):
        count = 0
        current = self.top
        while current:
            count += 1
            current = current.next
        return count

def interpret(commands):
    stack = Stack()
    for line in commands:
        parts = line.strip().split()
        cmd = parts[0]

        try:
            if cmd == "PUSH":
                value = int(parts[1])
                stack.push(value)

            elif cmd == "POP":
                stack.pop()

            elif cmd == "ADD":
                if stack.size() < 2:
                    raise Exception("Erro: falta elementos na pilha!")
                a = stack.pop()
                b = stack.pop()
                stack.push(b + a)

            elif cmd == "SUB":
                if stack.size() < 2:
                    raise Exception("Erro: falta elementos na pilha!")
                a = stack.pop()
                b = stack.pop()
                stack.push(b - a)

            elif cmd == "MUL":
                if stack.size() < 2:
                    raise Exception("Erro: falta elementos na pilha!")
                a = stack.pop()
                b = stack.pop()
                stack.push(b * a)

            elif cmd == "DIV":
                if stack.size() < 2:
                    raise Exception("Erro: falta elementos na pilha!")
                a = stack.pop()
                b = stack.pop()
                if a == 0:
                    raise Exception("Erro: Divisão por zero!")
                stack.push(b // a)

            elif cmd == "DUP":
                if stack.is_empty():
                    raise Exception("Erro: Pilha vazia para DUP!")
                stack.push(stack.peek())

            elif cmd == "SWAP":
                if stack.size() < 2:
                    raise Exception("Erro: Pilha insuficiente para SWAP!")
                a = stack.pop()
                b = stack.pop()
                stack.push(a)
                stack.push(b)

            elif cmd == "ROLL":
                n = int(parts[1])
                if n < 1 or n > stack.size():
                    raise Exception("Erro: n fora dos limites!")
                temp = []
                for _ in range(n - 1):
                    temp.append(stack.pop())
                nth = stack.pop()
                for item in reversed(temp):
                    stack.push(item)
                stack.push(nth)

            elif cmd == "CLEAR":
                stack.clear()

            elif cmd == "PRINT":
                values = stack.to_list()
                print(' '.join(map(str, reversed(values))) if values else '')

        except Exception as e:
            print(str(e))
            return

    # Imprimir pilha final se PRINT nunca foi chamado
    if "PRINT" not in [line.split()[0] for line in commands]:
        values = stack.to_list()
        print(' '.join(map(str, reversed(values))) if values else '')

# Leitura da entrada
n = int(input())
commands = [input() for _ in range(n)]
interpret(commands)
