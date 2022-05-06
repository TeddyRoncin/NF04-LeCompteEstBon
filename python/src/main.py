# On demande à l'utilisateur d'entrer les 3 valeurs
vals = [int(input("Entrez la " + i + " valeur : ")) for i in ["première", "deuxième", "troisième"]]
combinations = {}

for numberOfOperations in range(3):
    for i in range(4 ** numberOfOperations * 6):
        # On prend les 2 derniers chiffres de i, en forçant tous les autres à prendre la valeur 0
        # On récupère les opérations
        operations = [(i >> (2 * j)) & 0b11 for j in range(numberOfOperations)]
        swapOffset = numberOfOperations * 2
        # L'ordre dans lequel les valeurs seront envoyées pour calculer le résultat.
        order = list(vals)
        # Nous avons 3 swaps à faire
        for swap in range(3):
            # On regarde s'il y a un swap à faire
            if (i >> (swapOffset + swap)) & 1:
                # On fait le swap
                order[swap], order[swap-1] = order[swap-1], order[swap]
        # On calcul le résultat
        result = order[0]
        combin = str(order[0])
        skipped = False
        # On parcourt les opérations, ainsi que les valeurs à partir de la deuxième.
        # La première a déjà été traitée dans l'initialisation de la variable result
        for operation, val in zip(operations, order[1:]):
            if operation == 0:  # Addition
                result += val
                combin += " + " + str(val)
            elif operation == 1:  # Soustraction
                if result < val:  # Le résultat ne peut pas être négatif
                    skipped = True  # On se souvient que le calcul était impossible
                    break
                result -= val
                combin += " - " + str(val)
            elif operation == 2:  # Multiplication
                result *= val
                combin += " * " + str(val)
            else:  # Division
                if result % val != 0:  # La division doit tomber juste, le reste doit donc valoir 0
                    skipped = True  # On se souvient que le calcul était impossible
                    break
                result //= val  # Si on fait une division simple, le résultat sera un flottant
                combin += " / " + str(val)
        if not skipped:  # Si le calcul a été effectué sans opérations interdites
            print(combin)
            if not result in combinations:
                combinations[result] = combin + " = " + str(result)

for possibleResult in sorted(combinations.keys()):
    print(str(possibleResult) + " (" + combinations[possibleResult] + ") ")