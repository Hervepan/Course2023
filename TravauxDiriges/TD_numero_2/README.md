# TP2 de PAN Herve - LEBRET Chloe

`pandoc -s --toc tp2.md --css=./github-pandoc.css -o tp2.html`

# Question de cours

## Première question

Dans le cas du cours, 0 envoie un message a 2 de manière *synchrone* , 1 envoie un message à 2 de manière *synchrone*. Le processus 2 lui  attend la réception d'un message par n'importe autre processus, à la réception de celui ci, il envoie un message à 0 et finalement réceptionne le deuxième message. 

==Situation avec interblocage==

Si 2 reçoit le message envoyé par le processus 1 en premier, il va envoyer un message à 0.
On rencontre alors une situation de blocage puisque 0 ne pourra jamais recevoir ce message, son message envoyé de manière synchorne ne sera jamais reçu 

==Situation sans interblocage==

2 reçoit le message de 0 en premier, ainsi il peut envoyé son propre message à 0, et puis il recevra le message envoyé par 1.

## Seconde question 

D'après la loi d'Ahmdal on a :

$$ S(n) = {n \\over 1+(n-1)f} $$

pour n très grand on obtient : 

$$ S(n) = {1 \\over f} $$ 



## Mandelbrot 

*Expliquer votre stratégie pour faire une partition équitable des lignes de l'image entre chaque processus*

           | Taille image : 800 x 600 | 
-----------+---------------------------
séquentiel |              
1          |              
2          |              
3          |              
4          |              
8          |              


*Discuter sur ce qu'on observe, la logique qui s'y cache.*

*Expliquer votre stratégie pour faire une partition dynamique des lignes de l'image entre chaque processus*

           | Taille image : 800 x 600 | 
-----------+---------------------------
séquentiel |              
1          |              
2          |              
3          |              
4          |              
8          |              



## Produit matrice-vecteur



*Expliquer la façon dont vous avez calculé la dimension locale sur chaque processus, en particulier quand le nombre de processus ne divise pas la dimension de la matrice.*
