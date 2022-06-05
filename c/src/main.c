// Bonjour :)
#include <stdio.h>

// Quelques définitions de noms qui rendent la représentation d'opérations plus claire
#define ADDITION 0
#define SOUSTRACTION 1
#define MULTIPLICATION 2
#define DIVISION 3

int main() {
    // On ouvre le fichier "combinations" en lecture
    FILE *file = fopen("combinations", "r");
    if (!file) {  // Si file == NULL, il y a eu une erreur : fichier non existant, fichier déjà ouvert dans un autre programme, ...
        printf("Une erreur s'est produite en ouvrant le fichier \"combinations\". Verifiez que le fichier existe dans le répertoire depuis lequel vous lancez le programme et que vous ne l'avez pas ouvert dans un autre programme");
        return 1;
    }
    // Entrée des 3 valeurs de l'utilisateur
    int values[3];
    for (int i = 0; i < 3; i++) {
        printf("Entrez le nombre %d :", i+1);
        scanf("%d", &values[i]);
    }
    int c;  // Le caractère courant
    int fileEnd = 0;  // Si on a fini de lire le fichier. Si c == EOF, alors on est arrivé à la fin du fichier

    // Le stockage des différents résultats que l'on a trouvés, pour éviter de donner certains résultats plusieurs fois à l'utilisateur
    // (par exemple, avec 1, 2 et 3, on peut faire plusieurs fois le nombre 1 : 2 - 1 = (1 + 2) / 3 = 1)
    // 74 est le nombre de combinaisons d'opérations possibles
    // On crée aussi une simple variable de compteur pour savoir où on en est dans le tableau
    int possibleResults[74];
    int possibleResultsCount = 0;

    // Boucle principal : lit une ligne et calcule le résultat associé à cette ligne
    while (!fileEnd) {
        int stop = 0;  // Calcul impossible ?
        int result = 0;  // Résultat du calcul, est modifié au fur et à mesure que l'on lit la ligne
        int operation = ADDITION;  // La dernière addition lue. Par défaut, c'est l'addition : quand on traitera le premier nombre, on aura result = 0 + nombre
        int computation[5];  // La trace de notre calcul. Les 5 entiers peuvent permettre de stocker jusqu'à 3 nombres et 2 opérateurs, soit le calcul le plus long autorisé
        int computationSize = 0;  // La taille de notre calcul. C'est la somme du nombre de termes et d'opérations. Par exemple, 1 + 2 a une longueur de 3 (2 nombre et 1 opération)
        // Boucle qui lit un calcul. S'arrête quand le calcul est impossible ou quand on est arrivé à la fin de la ligne
        while (!stop && (c = getc(file)) != '\n') {
            // Les caractères représentent les nombres du tableau "values"
            if ('a' <= c && c <= 'c') {
                int value = values[c - 'a'];  // "c - 'a'" retournera 1, 2, ou 3 en fonction de la valeur de c
                // On regarde ce qu'il faut faire avec ce nombre. Par exemple, si c'est une multiplication, il faut multiplier le résultat par "value"
                switch (operation) {
                    case ADDITION:
                        result += value;
                        break;
                    case SOUSTRACTION:
                        // Il faut gérer le cas où on ne peut pas faire la soustraction
                        // Si on ne peut pas la faire, le résultat ne sera pas utilisé, on peut donc le modifier sans rien affecter. On n'a pas besoin d'inverser le calcul
                        result -= value;
                        stop = result < 0;
                        break;
                    case MULTIPLICATION:
                        result *= value;
                        break;
                    case DIVISION:
                        // Il faut gérer le cas où on ne peut pas faire la division
                        // Si on ne peut pas la faire, le résultat ne sera pas utilisé, on peut donc le modifier sans rien affecter. On n'a pas besoin d'inverser le calcul
                        stop = result % value != 0;
                        result /= value;
                        break;
                    default:  // Le default ne sera jamais exécuté
                        break;
                }
                // On se souvient de cette étape
                computation[computationSize] = value;
            } else {  // Si ce n'était pas 'a', 'b' ou 'c', alors on interprète directement le caractère
                switch (c) {
                    case '+':
                        operation = ADDITION;
                        break;
                    case '-':
                        operation = SOUSTRACTION;
                        break;
                    case '*':
                        operation = MULTIPLICATION;
                        break;
                    case '/':
                        operation = DIVISION;
                        break;
                    case EOF:
                        // On est arrivés à la fin du fichier.
                        // On arrête la boucle de lecture de ligne ainsi que celle de lecture du fichier (la boucle principale)
                        fileEnd = 1;
                        stop = 1;
                        break;
                    case ';':
                        // C'est un commentaire. On arrête donc la ligne
                        stop = 1;
                        break;
                    default:
                        // Le symbol n'est pas reconnu
                        printf("Fichier corrompu : symbole inconnu : %c (code %d)\n", c, c);
                        return 1;
                }
                // On se souvient de cette étape
                computation[computationSize] = c;
            }
            // Dans tous les cas, on a fait une étape en plus
            computationSize++;
        }
        // Si on a forcé la fin de lecture mais qu'on n'est pas à la fin du fichier, on n'est pas arrivé au bout de la ligne
        // On lit donc jusqu'à la fin de la ligne
        if (stop && !fileEnd) {
            while (getc(file) != '\n');
        } else {  // Si l'arrêt n'a pas été forcé (et donc que l'on n'est pas à la fin du fichier)
            // On cherche "result" dans "possibleResults", pour savoir s'il faut l'afficher à l'utilisateur ou non
            int found = 0;
            for (int j = 0; j < possibleResultsCount; j++) {
                if (possibleResults[j] == result) {
                    found = 1;
                }
            }
            // Si on n'avait encore jamais trouvé ce résultat, alors on stocke ce résultat dans "possibleResults", et on affiche le résultat
            if (!found) {
                possibleResults[possibleResultsCount++] = result;
                printf("%d [", result);
                // S'il y avait 2 calculs, on met des parenthèses, pour éviter d'écrire 2 + 1 * 3 = 9
                if (computationSize == 5) { printf("("); }
                for (int j = 0; j < computationSize; j++) {
                    // Si on est au 4ème caractère (index 3), alors "computationSize" vaut 5
                    // (elle est forcément impaire, sauf si le fichier est corrompu. Nous considérons qu'il ne l'est pas)
                    // On est alors après le deuxième nombre, il faut donc fermer la parenthèse
                    if (j == 3) { printf(")"); }
                    // 1 étape sur 2 devrait être un nombre, les autres devraient être des caractères représentant les calculs
                    printf(j % 2 == 0 ? "%d" : " %c ", computation[j]);
                }
                printf(" = %d]\n", result);
            }
        }
    }
    // On ferme le fichier
    fclose(file);
    // Et c'est fini. Bonne journée :)
    return 0;
}