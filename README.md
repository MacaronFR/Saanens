Saanens
=
Interpréteur de Saanens et IDE

Par TURBIEZ Denis et BOUDEDJA Kamilia

Développer en C

Utilisation de la bibliothèque Gtk+

##**Mot clés et signification**

### bouc => Boucle itérative
```
bouc(variable = début; condition d'arrêt; instruction à executer a chaque tour)
#code à itérer
finbouc;
```

###fromage => boucle conditionnnelle à zéro itération minimum
```
fromage(condition)
#code a itérer
finfromage;
```

###lait … fromage => boucle conditionnelle à une itération minimum
```
lait
#code a itérer
fromage(condition);
```

###chevre … chevrau … brebis … breche … finchevre => condition
```
chevre(condition1)
chevreau
    #si condition1 vraie
breche(condition2) #si condition2 fausse
    chevreau
        #si condition2 vraie
    brebis
        #si condition 2 fausse
    finchevre #fin condition2
finchevre #fin condition1
```

###troupeau … espece … cassemire => condition à multiple résultat
```
troupeau(expression)
    espece (correspondance1): #code à executer 
        cassemire; # fin correspondance 1
    espece (correspondance2): #code à executer
        #correspondance 2 continue a l'espece suivante 
    espece (correspondance3): #code à executer 
        cassemire; # fin correspondance 2 et 3
    …
    espece (correspondanceN): #code à executer
        cassemire; #fin correspondance N 
fintroupeau
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
++ incrémentation
-- décrémentation
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
###*À venir*