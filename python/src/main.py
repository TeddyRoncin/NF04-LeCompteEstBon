# On demande à l'utilisateur d'entrer les 3 valeurs
vals = [int(input("Entrez la " + i + " valeur : ")) for i in ["première", "deuxième", "troisième"]]

# Nous avons un total de 3! * 4^2 = 96 arrangement possible des opérations
# 3! est le nombre d'arrangement des nombres et 4^2 est le nombre d'arrangement des opérateurs
# Nous allons donc utiliser un compteur (variable i) qui sera un entier allant de 0 à 3! * 2^4 - 1,
# c'est-à-dire un byte allant de 0000000 à 1011111 en binaire
# On représentera les opérations sur 2 bits de la façon suivante :
#   - 00 : addition
#   - 01 : soustraction
#   - 10 : multiplication
#   - 11 : division
# On représentera l'ordre dans lequel on doit afficher les valeurs de la manière suivante :
#   - Tout d'abord, on crée une copie de la liste, de façon à ce qu'elle soit à chaque fois dans cet order : [val1, val2, val3]
#   - Si le premier bit est un 1, alors la première valeur de vals sera échangée avec la deuxième valeur de vals
#   - Si le deuxième bit est un 1, alors la deuxième valeur de vals sera échangée avec la troisième valeur de vals
#   - Si le troisième bit est un 0, alors on regardera d'abord le premier bit. Sinon, on regardera d'abord le second
# Les 2 derniers chiffres de notre compteur (variable i) représentent la première opération à effectuer.
# Les 2 chiffres avant ceux-ci représentent la deuxième opération à effectuer
# Enfin, les 3 premiers chiffres représentent l'ordre dans lequel on affichera les valeurs.

combinations = {}

for numberOfOperations in range(3):
    for i in range(4 ** numberOfOperations * 8):
        # On prend les 2 derniers chiffres de i, en forçant tous les autres à prendre la valeur 0
        # On récupère les opérations
        operations = [(i >> (2 * j)) & 0b11 for j in range(numberOfOperations)]
        print(i, operations)
        swapOffset = numberOfOperations * 2
        # L'ordre dans lequel les valeurs seront envoyées pour calculer le résultat
        order = list(vals)
        swap = i & (1 << swapOffset) != 0
        # Nous avons 2 swaps à faire. A la fin de la boucle, on changera la valeur de swap (si swap = 1, swap vaudra 0, si swap = 0, swap vaudra 1)
        for j in range(2):
            if (i >> (swapOffset + 2 - swap)) & 1:
                order[swap], order[swap+1] = order[swap+1], order[swap]
            swap = not swap
        # On calcul le résultat
        result = order[0]
        combin = str(order[0])
        skipped = False
        for operation, val in zip(operations, order[1:]):
            if operation == 0:
                result += val
                combin += " + " + str(val)
            elif operation == 1:
                if result < val:
                    skipped = True
                    break
                result -= val
                combin += " - " + str(val)
            elif operation == 2:
                result *= val
                combin += " * " + str(val)
            else:
                if result % val != 0:
                    skipped = True
                    break
                result //= val  # Si on fait une division simple, le résultat sera un flottant
                combin += " / " + str(val)
        if not skipped:
            if not result in combinations:
                combinations[result] = combin + " = " + str(result)

for possibleResult in sorted(combinations.keys()):
    print(str(possibleResult) + " (" + combinations[possibleResult] + ") ")