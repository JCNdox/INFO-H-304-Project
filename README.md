# INFO-H304-Project

## 1. Usage
* Les fichiers sont compilés en utilisant la commande make
* Pour executer le programme il suffit d'utiliser la commande : ./projet  queryfile databasefilename
* On peut rajouter un troisième paramètre permettant de charger une autre matrice Blosum :
  ./projet queryfile databasefilename BLOSUM
* On peut également rajouter en paramètre les gap open et extension : `
  ./projet queryfile database filename gapopen gapextension
* Et on peut combiner les deux :
  ./projet queryfile databasefilename gapopen gapextension BLOSUM
 

## 2. Code
* Le code lit le fichier .psq puis extrait une chaine avant de la comparer a une chaine cible en utilisant l'algorithme de SW
* Après cela il lit le nom de la chaine dans le fichier .phr
* En dernier lieu un tri est effectué et par défaut les 5 meilleurs résultats sont gardés en mémoire (On peut changer ce nombre via #define RESULTAFFICHE 5 dans main.cpp)

## 3. Limitations
* Lorsqu'on lit les données du fichier .pin sur une base de données personnalisée on rencontre parfois des problèmes de lecture. On ne retrouve pas ces problèmes lorsque l'on lit la base de données complète
* L'aspect optimisation et vitesse du code a été laissé de côté
