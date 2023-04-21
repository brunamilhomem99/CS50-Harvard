import math

input_str = input("Text: ")

# declarando as variáveis para checar a quantidade de letras
letters = 0
cont_symbols = 0
cont_spaces = 0


# percorre o input do usuário caracter a caracter
for char in input_str:

    # checagem de alfanumérico
    if char.isalnum():
        letters += 1

    # checagem de símbolos
    if char in ['.', '?', '!']:
        cont_symbols += 1

    # checagem de espaços
    if char.isspace():
        cont_spaces += 1

# quantidade de símbolos (pontuação) = quantidade de sentenças
sentences = cont_symbols

# quantidade de palavras = quantidade de espaços + 1
words = cont_spaces + 1

# cálculo de sentenças por 100 palavras
S = sentences / words * 100

# cálculo de letras por 100 palavras
L = letters / words * 100

# índice de coleman-liau
index = 0.0588 * L - 0.296 * S - 15.8

# arrendondamento da variável
grade = round(index)

# imprimindo a grade correspondente
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f'Grade {grade}')
