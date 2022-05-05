# Le compte est bon - Mini projet de NF04 du semestre P22

## Sommaire
1 [Rappel du sujet](#1-rappel-du-sujet)<br />
&nbsp;&nbsp;&nbsp;&nbsp;1.1 [Le sujet](#11-le-sujet)<br />
&nbsp;&nbsp;&nbsp;&nbsp;1.2 [Ce qu'il faut faire](#12-ce-quil-faut-faire)<br />
2 [Vocabulaire et notions utilisées](#2-vocabulaire-et-notions-utiliss)<br />
&nbsp;&nbsp;&nbsp;&nbsp;2.1 [Vocabulaire](#21-vocabulaire)<br />
&nbsp;&nbsp;&nbsp;&nbsp;2.2 [Notions](#22-notions)<br />
3 [Programme en C](#3-programme-en-c)<br />
4 [Programme en Python](#4-programme-en-python)<br />
&nbsp;&nbsp;&nbsp;&nbsp;4.1 [Approche](#41-approche)<br />
&nbsp;&nbsp;&nbsp;&nbsp;4.2 [Représentation binaire des opérateurs](#42-reprsentation-binaire-des-oprations)<br />
&nbsp;&nbsp;&nbsp;&nbsp;4.3 [Représentation binaire d'un arrangement de 3 nombres](#43-reprsentation-binaire-dun-arrangement-de-3-nombres)<br />
&nbsp;&nbsp;&nbsp;&nbsp;4.4 [Décodage complet d'un nombre](#44-dcodage-complet-dun-nombre)<br />

## 1 Rappel du sujet

### 1.1 Le sujet

Le but du jeu est de trouver tous les nombres pouvant être créés à partir de 3 nombres saisis par l'utilisateur et des 4 opérations élémentaires : l'addition, la soustraction, la multiplication, et la division.

Notons que la soustraction `a - b` ne peut être effectuée que lorsque `a >= b`

On ne peut pas utiliser plusieurs fois le même nombre, et on n'est pas obligés d'utiliser tous les nombres

### 1.2 Ce qu'il faut faire

Il faut créer ce programme dans les langages C et Python.

Nous ne pouvons pas créer de fonctions (sauf fonctions simples)


## 2 Vocabulaire et notions utilisés

### 2.1 Vocabulaire

* _swap_ : un échange de 2 nombres

### 2.2 Notions

Ces algorithmes se basent sur la représentation des nombres en binaire.

On lira les bits de la droite vers la gauche. Ainsi, dans le nombre `01100101`, le 1er bit vaudra 1, et le 8ème vaudra 0

Il existe quelques opérateurs importants :
* `a << b` : le décalage vers la gauche. Décale `a` de `b` bits. Les bits rajoutés à droite valent 0. Les bits qui ne peuvent pas être stockés à gauche (par exemple, on ne peut pas stocker de 9ème bit dans un octet = 8 bits) sont effacés. Cela est équivalent à `(a x 2^b) % N`, où `N` est la valeur maximale encodable (256 pour un octet)

    Exemple : `01011101 << 3 = 11101000`

* `a >> b` : le décalage vers la droite. Décale `a` de `b` bits. Les bits rajoutés à gauche valent 0. Les bits qui ne peuvent pas être stockés à droite (par exemple, on ne peut pas stocker de 0ème bit) sont effacés. Cela est équivalent à `E(a / 2^b)`, où `E(x)` est la fonction partie entière

    Exemple : `01011101 >> 3 = 00001011`

* `a & b` : ET binaire. Agit comme un opérateur ET pour chaque bit des 2 nombres

    Exemple : `01011001 & 10011101 = 00011001` : seuls les bits 1, 4 et 5 valent 1 dans les 2 nombres

Cela nous permet de faire des opérations très utiles

* Récupérer le `n`-ième bit d'un nombre `a` : Il faut isoler ce bit. Pour cela, on place ce bit en première position (`b = a >> (n - 1)` : on soustrait 1 à n car on commence à compter à partir de 1, mais la valeur nulle de l'opérateur est 0). Il faut ensuite faire en sorte que tous les bits soient égaux à 0, sauf le premier, de façon à isoler le bit (`b & 1`). Pour récupérer le `n`-ième bit du nombre `a`, on fera donc `(a << (n - 1)) & 1`

## 3. Programme en C

## 4. Programme en Python

### 4.1 Approche

Le but est de parcourir les nombres et de trouver quelle combinaison de nombres et d'opérations chaque nombre représente
On fera 2 boucles principales, imbriquées les unes dans les autres.
La première boucle comptera le nombre d'opérations que l'on fera (entre 0 et 2). La seconde sera la boucle qui permettra de parcourir les nombres

### 4.2 Représentation binaire des opérations

Une opération est définie sur 2 bits. Voici le tableau de représentation des opérations :

|       00 |           01 |             10 |     11   |
|----------|--------------|----------------|----------|
| Addition | Soustraction | Multiplication | Division |

### 4.3 Représentation binaire d'un arrangement de 3 nombres

Un arrangement de 3 nombres est défini sur 3 bits.

Tout d'abord, on stocke ces 3 nombres dans un tableau. L'ordre est important, il doit toujours être le même à chaque décoder d'un nombre


Si le premier bit vaut 1, alors on échange les 2 premiers nombres du tableau de nombres

Si le deuxième bit vaut 1, alors on échange les 2 derniers nombres du tableau de nombres

Le troisième bit nous dit quel _swap_ faire en premier : s'il vaut 0, alors traite d'abord le premier bit. Sinon, on traite d'abord le deuxième bit

**Exemple :**

Prenons le nombre 3 dont la représentation binaire est `011`. La liste de nombre est : `1, 2, 3`

Tout d'abord, on regarde le dernier bit. Ici, il vaut 1. On traite donc le deuxième bit, puis le premier

Le deuxième bit vaut 1, on fait donc un _swap_ entre la deuxième et la troisième valeur de la liste. On obtiens ainsi la liste `1, 3, 2`

Le troisième bit vaut 0, on ne fait donc pas de _swap_.

L'arrangement représenté par le nombre 3 est donc `1, 3, 2`

### 4.4 Décodage complet d'un nombre

On appelle `n` le nombre d'opérations

* Les `n`x2 derniers bits permettent de décrire les opérations
* Les 3 derniers bits permettent de décrire l'arrangement des nombres

**Exemple : **

Prenons `n` = 2, et essayons de décoder le nombre 105, dont la représentation binaire est `1101001`. Supposons que notre liste de nombre soit `1, 2, 3`

Puisque `n` = 2, on a 2 opérateurs, notre calcul sera donc de la forme :
`(a <opérateur> b) <opérateur> c`

* Premier opérateur : on prend les 2 derniers bits, qui sont `01`. Ce code représente la soustraction, donc le calcul est de la forme `(a - b) <opérateur> c`
* Deuxième opérateur : on prend les 2 bits précédents, qui sont `10`. Ce code représente la multiplication, donc le calcul est de la forme `(a - b) x c`
* Sens des _swaps_ : le troisième bit vaut 0, on traite donc d'abord le premier bit
* _Swap_ des 2 premières valeurs : le premier bit vaut 1, on échange donc les 2 premières valeurs de notre liste. Celle-ci vaut désormais `2, 1, 3`
* _Swap_ des 2 dernières valeurs : le deuxième bit vaut 1, on échange donc les 2 dernières valeurs de notre liste. Celle-ci vaut désormais `2, 3, 1`
* Calcul : en remplaçant `a`, `b` et `c` par les valeurs de la liste, on obtient le calcul `(2 - 3) x 1`. On doit d'abord calculer `2 - 3`. 2 étant inférieur à 3, on ne peut pas effectuer ce calcul, le calcul représenté par le nombre 105 n'est donc pas possible dans les règles que nous nous sommes fixées.
