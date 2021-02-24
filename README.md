Saanens
=
Interpréteur de Saanens et IDE

Par TURBIEZ Denis et BOUDEDJA Kamilia

Développer en C

Utilisation des bibliothèques :
- gtk+3
- regex
- readline/history

##**Mot clés et signification**

### bouc => Boucle itérative (coming soon)
```
bouc(variable = début; condition d'arrêt; instruction à executer a chaque tour):
#code à itérer
finbouc;
```

###fromage => boucle conditionnnelle à zéro itération minimum
```
fromage(condition):
#code a itérer
finfromage;
```

###lait … fromage => boucle conditionnelle à une itération minimum (coming soon)
```
lait:
#code a itérer
fromage(condition);
```

###chevre … chevrau … breche … finchevre => condition
```
chevre(condition1):
chevreau:
    #si condition1 vraie
brebis: #si condition1 fausse
    brebis(condition2):
    chevreau:
        #si condition2 vraie
    brebis:
        #si condition 2 fausse
    finchevre; #fin condition2
finchevre; #fin condition1
```

###troupeau … espece … cassemire => condition à multiple résultat (coming soon)
```
troupeau(expression):
    espece (correspondance1): #code à executer 
        cassemire; # fin correspondance 1
    espece (correspondance2): #code à executer
        #correspondance 2 continue a l'espece suivante 
    espece (correspondance3): #code à executer 
        cassemire; # fin correspondance 2 et 3
    …
    espece (correspondanceN): #code à executer
        cassemire; #fin correspondance N 
fintroupeau;
```

##Opérateurs
###Comparaisons
```
== => égalité
<> => différence
< => strictement inférieur
> => strictement supérieur
<= => inférieur ou égale
>= => supérieur ou égale
```
###Affectation
```
= => affectations
++ incrémentation (coming soon)
-- décrémentation (coming soon)
```
###Algébrique
```
+ => addition
- => soustraction
* => multiplication
/ => division
% => reste de la division entière
```

##Types
```
int => entier
float => réel
char => caractère
string => chaine
bool => booléen
```

##Fonction

###Cast
```
int(operateur); => renvoie opérateur sous la forme d'un int
float(operateur); => renvoie opérateur sous la forme d'un float
char(operateur); => renvoie opérateur sous la forme d'un char
string(operateur); => renvoie opérateur sous la forme d'un string
bool(operateur); => renvoie opérateur sous la forme d'un bool
```

###I/O
```
print(expression); => evalue expression et l'affiche
scanf(expression); => evalue expression, l'affiche et attend une entrée utilisateur
```