from cs50 import get_string

# biblioteca para expressões regulares
import re


def main():
    number = get_string("Number: ")    # input do usuário

    # definindo as expressões regulares para cada tipo de cartão
    americanEx = "^3[47][0-9]{13}$"
    masterCard = "^5[1-5][0-9]{14}$"
    visa = "^4[0-9]{12,15}$"

    # criando uma lista de inteiros com o valor armazenado em "number"
    # "*number" descompacta os caracteres da string p/ transformarem-se em ints pela funçao map
    cardigits = list(map(int, [*number]))
    lenCardigits = len(cardigits) - 2    # armazenando o comprimento da lista de inteiros numa variável
    numFinal = 0    # declarando a vairável que será usada para armazenar as somas dos números
    check = False    # variável declarada false fora do loop de verificação caso número seja inválido

    # loop para multiplicar os dígitos alternadamente
    for i in range(lenCardigits, -1, -2):
        num = cardigits[i] * 2
        if num > 9:
            num -= 9
        numFinal += num
    lenCardigits += 1

    # loop para incrementar os dígitos que sobraram a variável numFinal
    for i in range(lenCardigits, -1, -2):
        numFinal += cardigits[i]
    if numFinal % 10 == 0:
        check = True

    # comparando o valor dado em no input com as expressões regulares de cada cartão
    if re.fullmatch(americanEx, number) and check:
        print('AMEX\n')
    elif re.fullmatch(masterCard, number) and check:
        print('MASTERCARD\n')
    elif re.fullmatch(visa, number) and check:
        print('VISA\n')
    else:
        print('INVALID\n')
        
        
main()