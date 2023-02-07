# TP2 de PAN Herve - LEBRET Chloe

`pandoc -s --toc tp2.md --css=./github-pandoc.css -o tp2.html`

# Question de cours

## Première question

Dans le cas du cours, 0 envoie un message a 2 de manière *synchrone* , 1 envoie un message à 2 de manière *synchrone*. Le processus 2 lui  attend la réception d'un message par n'importe autre processus, à la réception de celui ci, il envoie un message à 0 et finalement réceptionne le deuxième message. 

**Situation avec interblocage**

Si 2 reçoit le message envoyé par le processus 1 en premier, il va envoyer un message à 0.
On rencontre alors une situation de blocage puisque 0 ne pourra jamais recevoir ce message, son message envoyé de manière synchorne ne sera jamais reçu 

**Situation sans interblocage**

2 reçoit le message de 0 en premier, ainsi il peut envoyé son propre message à 0, et puis il recevra le message envoyé par 1.

## Seconde question 

D'après la loi d'Ahmdal on a :

$$ S(n) = {n \\over 1+(n-1)f} $$

pour n très grand on obtient : 

$$ S(n) = {1 \\over f} $$ avec f la fraction de temps non parallélisable. Donc ici $$ f = 0.1$$

L'accélération maximale atteignable est de 10

Puisque qu'elle obtient une accélération maximale de 4, il semble que 4 noeuds de calcul semble être le bon choix.

D'après la loi de Gustafon on a : 

$$ S(n) = n + (1-n)s $$

avec s la proportion de temps passé en séquentiel.
Ici on a choisi n = 4 :
on a donc 

$$ S(n) = 3,7 $$ 

## Mandelbrot 

On va diviser le nombre de ligne par le nombre de processus actifs. 
Puisqu'on utilise un gather pour récuperer toutes les données, il faut que le nombre de ligne = 600 doit être divisble par le nombre de processus actif

           | Taille image : 800 x 600 | speed_up 
-----------+--------------------------|------------
Séquentiel|99.0591|1
2|49.8853|0.50359129
3|37.9914|0.383522564
4|29.7911|0.300740669
6|26.4884|0.267399966
8|29.3877|0.296668353

Ici on observe que le temps n'augmente pas linéairement comme on pourrait l'imaginer. Cela conforte la loi d'Ahmdal.
En regardant de plus près les résultats on remarque que c'est souvent les process qui obtiennent des lignes situés vers la fin de l'image qui bloque le programme. 
Par exemple : pour 8 processus, le processus 1 et 2 finissent en seulement 1 seconde alors que le processus de rang 7 lui prend 30 sec 

Pour l'attribution dynamique, on va mettre en oeuvre la stratégie de mettre esclave. Dès qu'un processus a fini de calculer une ligne, il va recevoir par le processus maitre (ici ce sera 0) une nouvelle ligne a calculé. 


           | Taille image : 800 x 600 | 
-----------+---------------------------
séquentiel |              
1          |              
2          |              
3          |              
4          |              
8          |              



## Produit matrice-vecteur

### Produit parallèle matrice - vecteur par colonne 

Pour avoir la dimension locale pour chaque processus, si le nombre de processus divise N (nombre de colonne) alors il suffira d'attribuer des matrices de dimension N*(N/nbp) avec nbp le nombre de processus.

De même il faudra découper le vecteur en npb partie égale pour l'attribuer a chaque processus

Dans le cas ou N n'est pas divisible par nbp, soit R le reste de la division euclidienne N par nbp. On formera alors R bloc de taille N/nbp + 1 et le reste des blocs seront de taille N/nbp

Dans ce cas la il faudra aussi faire attention a la découpe de notre vecteur 

Dans les deux on finira avec un MPI_Reduce pour avoir la somme totale du vecteur

### Produit parallèle matrice - vecteur par ligne

L'idée de découpage par ligne est exactement la même que dans le cas précedent. 

On fera exactement la même chose que dans la de bloc par colonne (On fait le même process que par colonne sur la transposé de la matrice).

Pour avoir la vecteur finale, il faudra simplement utiliser un MPI_Gather pour obtenir le résultat.