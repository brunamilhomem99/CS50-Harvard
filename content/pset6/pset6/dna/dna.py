# biblioteca para linha de comando
from sys import argv

# biblioteca para ler aquivo CSV
from csv import reader

# biblioteca para expressões regulares
from re import finditer


# verificando se foram fornecidos argumentos suficientes
if len(argv) != 3:
    print("Usage: pyhton dna.py data.csv sequence.txt")
    exit()

# armazenando o nome dos arquivos de entrada
database_name = argv[1]    # nome do arquivo CSV com os dados da população
sample_name = argv[2]    # nome do arquivo TXT com o DNA dos suspeitos

# criando um dicionário para armazenar os dados
database = {}
seqs = None

# abrindo o arquivo CSV do bando de dados e lendo os dados
with open(database_name, "r") as f:
    # a função reader leva como argumento um indicador de sepaação do texto (vírgula, nesse caso)
    csv_reader = reader(f, delimiter=',')
    first_line = True
    for row in csv_reader:
        if first_line:
            # a primeira linha contém os nomes das sequencias
            seqs = [row[i] for i in range(1, len(row))]
            first_line = False
        else:
            # cada linha subsequente cotém os dados de uma pessoa
            # armazenamos esses dados em um dic com as sequências como chaves
            database[row[0]] = {seqs[i - 1]: int(row[i]) for i in range(1, len(row))}

# criando um dicionário para armazenar as sequências do DNA do suspeito
sample = {seq: 0 for seq in seqs}

# abrindo o arquivo TXT com  DNA  do suspeito e lendo os dados
with open(sample_name, "r") as f:
    dna = f.read()
    # para cada sequência no dicionário do suspeito, procuramos correspondências no DNA
    for seq in sample:
        matches = []
        # usando uma expressão regular para encontrar todas as ocorrências da sequeência do DNA
        for match in finditer(rf'({seq})+', dna):
            matches.append(match.group())
        # se não há correspondencia o suspeito é desconsiderado
        if matches == []:
            break

        # comparando o comprimento da correspondência mais longa com a original
        longest_seq = max(matches)
        sample[seq] = len(longest_seq) / len(seq)

# verificando se o DNA  do suspeito corresponde a algum indivíduo do database
match = False
for person in database:
    if all(database[person][seq] == sample[seq] for seq in seqs):
        print(person)
        match = True
# caos não haja correspondências:
if match == False:
    print("No match")
