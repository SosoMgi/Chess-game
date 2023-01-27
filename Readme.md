# Readme


## Usage

To compile use

```bash
    make
```

To cleanup compilation files

```bash
    make
    make clean
```

To run the programm simply execute: make then `./bin/echecs`
*Tested on Ubuntu 18 and WSL1*

To run tests use

```bash
    make
    make test
```

To run doxyfile

```bash
    make docs
```

## Documentation

See in `doc/html/` folder

## Note sur le projet:

Ce qui est fonctionnel:
    -Fonctionnalité de base
    -prise
    -Pion
    -Obstacle
    -Promotion
    -Echec
    -Roque
    -Echec et mat
    -Pat

La structure de mon projet suit en grande partie la structure
conseillé par l'énnoncé.
J'ai donc une classe Square qui représente les cases du plateau,
Une classe Piece qui représente l'abstraction d'une pièce et une sous-classe
par pièce qui en hérite. Enfin, il y a deux autres classes: Echequier et Jeu 
qui gouvernent les actions sur l'échéquier et le déroulement du jeu global.


Déroulement du projet:

1) 
    J'ai commencé par créer les classes Square et Piece avec ses sous-classes.
Je me suis attardé sur les mouvements légaux puisque je ne savais pas jouer aux échecs.

2)
    J'ai rapidement codé les fonctions qui étaient en grande partie données.

3)
    Je me suis attardé sur la régle d'echec. En effet, à partir de se moment,
le niveau de difficulté à fortement augmenté. Pour tester tout les mouvements possibles
et revenir au point de jeu avant les testes d'echec et mat (qui oblige à déplacer de pièces), j'ai trouvé comme seule solution
de cloner la grille de jeu. Ainsi, tout les mouvement effectué dans l'algorithme de détermination
d'echecs sont vu comme fictif. En revanche, bien que les mouvements n'étaient pas sauvegardés, les attributs
de classe eux l'étaient. D'où la présence du booléen et la méthode Echequier::mvt(). Udapte_position fait la 
même chose mais à plus grande échelle. Utile pour echec et mat.
    Cependant, j'ai remarqué que les pièces ne sont pas clonées puisqu'elles sont enregistrées dans le tas, là 
où le reste des variables sont dans la pile. Donc les piéces sont communes à tout les plateau de jeux. 
Ainsi, libérer la mémoire d'une pièce un plateau la libéré aussi sur les autres plateaux. C'est pour cela qu'il y a un booléen en argument sur les fonctions de mouvement pour savoir si ce movement est fictif ou non, est donc si on doit libérer
la mémoire ou non.

4)
    Pour le pat et l'échec et mat, je l'ai implémenté de façon naïf. On regarde toutes les cases. Si la case 
est accessible par mvt_legal() et si elle empêche l'echec, alors on return false.


Difficultés:
    -Apprendre les règles.
    -Gestion de la mémoire.
    -Connecter Echequier et Piece sans redondance
    -Algorithmes



