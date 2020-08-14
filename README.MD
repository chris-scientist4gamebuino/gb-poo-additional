
# Posons les concepts relatifs à la POO puis au MVC

## Exemple

Dans cet article, nous allons programmer un mini jeu.

Le seul élément de gameplay est de faire bouger un personnage, représenté par un `x`, sur une partie de l'écran.

Rien de transcendant, mais l'objectif est de voir l'évolution du programme procédural à une version Modèle Vue Contrôleur (MVC), en passant par un programme orienté objet.

## La programmation procédurale

Pour gérer notre personnage, nous avons besoin de stocker en mémoire ces coordonnées.

Notre programme pourrait ressembler à ceci ([une version téléchargeable est disponible ici](https://github.com/chris-scientist/gb-sample/archive/v1.0.zip)) :

```cpp
#include <Gamebuino-Meta.h>

// position du personnage
int xCharacter;
int yCharacter;

void setup() {
  // initialiser la gambuino
  gb.begin();

  // initialisation de la position du personnage
  xCharacter = 10;
  yCharacter = 5;
}

void loop() {
  // boucle d'attente
  while(!gb.update());

  // effacer l'écran
  gb.display.clear();

  manageMove();
  paint();
}

// Gérer les déplacement
void manageMove() {
  // Note :
  // * Le test : (yCharacter > 0) permet de ne pas sortir du haut de l'écran.
  // * Le test : (xCharacter < 19) permet de ne pas sortir de la droite de l'écran.
  // * Le test : (yCharacter < 9) permet de ne pas sortir du bas de l'écran.
  // * Le test : (xCharacter > 0) permet de ne pas sortir de la gauche de l'écran.
  // Ainsi on définit les limites du personnage.
  if(gb.buttons.pressed(BUTTON_UP)) {
    if(yCharacter > 0) {
      yCharacter--;
    }
  } else if(gb.buttons.pressed(BUTTON_RIGHT)) {
    if(xCharacter < 19) {
      xCharacter++;
    }
  } else if(gb.buttons.pressed(BUTTON_DOWN)) {
    if(yCharacter < 9) {
      yCharacter++;
    }
  } else if(gb.buttons.pressed(BUTTON_LEFT)) {
    if(xCharacter > 0) {
      xCharacter--;
    }
  }
}

// Gérer l'affichage
void paint() {
  for(int y=0 ; y<=yCharacter ; y++) {
    for(int x=0; x<20 || x<xCharacter ; x++) {
      if(x == xCharacter && y == yCharacter) {
        gb.display.print("x"); // afficher le personnage
      } else {
        gb.display.print(" "); // afficher une colonne vide
      }
    }
    gb.display.println(); // passage à la ligne suivante
  }
}
```

Note : Dans cette version nous avons placé tout le code dans un seul fichier par simmplicité. Mais dans un programme plus complexe il est nécessaire de placer le code dans différents fichier.

Nous avons ainsi créer deux fonctions :
* `managedMove` pour gérer les déplacements ;
* `paint` pour dessiner le personnage.

Voyons comment faire ce même programme dans une version dite orienté objet.

## La programmation orientée objet

### Quésaco ?

La POO est un paradigme ! Il s'agit d'une façon de concevoir un programme.

### Quelques précisions

En POO le concept incontournable et l'élément de base est : la classe.

Il s'agit d'un structure de données, qui a :
* des variables membres, on parle d'attributs ;
* des fonctions membres, on parle de méthodes.

Ainsi nous allons déclarer une classe nommé `Character` ! Notez bien le **C** majuscule au début du noms, il s'agit d'une convention, qu'il est fortement recommandé de suivre.

Notre classe aura comme attributs les coordonnées. Et elle aura deux méthodes : l'une pour la gestion des commandes, l'autre pour dessiner notre personnage.

En C++, on distingue la déclaration d'une classe, de sa définition. Dans la déclaration nous décrivons nos éléments (attributs et méthodes), mais sans implémenter nos méthodes, c'est-à-dire sans écrire ce qu'elles feront. C'est dans la définition que nous allons définir, implémenter nos méthodes.

Toujours en C++, la déclaration est placée dans un fichier `.h`, *h* comme header. Et la définition est placée dans un fichier `.cpp`.

### Passons au code !

Dans le fichier `Character.h` nous y trouverons le code suivant :

```cpp
#ifndef CHARACTER
#define CHARACTER

#include <Gamebuino-Meta.h>

class Character {
  private:
    uint8_t x;
    uint8_t y;
  public:
    Character();
    void manage();
    void paint();
};

#endif
```

Revenons sur plusieurs points :
* Une autre convention est : de nommer la déclaration de notre classe dans un fichier nommé *NomDeMaClasse.h*. De même la définition sera dans un fichier nommé *NomDeMaClasse.cpp*.
* Dans un projet plus complexe vous aurez sûrement besoin d'utiliser une classe dans plusieurs classes. Ainsi il est nécessaire de mettre des gardes fou grâce au instruction `ifndef`, `define` et `endif`.
* Avant la déclaration des attributs, il y a le mot-clé `private`. Cela signifie que les attributs sont ici privée. En programmation orienté objet, peu importe le langage, les attributs doivent être privée afin de respecter l'encapsulation. Ce mécanisme consiste à rendre les attributs inacessible en dehors des méthodes de la classe. Ceci dans le but de contrôler les données. Je ne vais pas m'étandre mais sacher que pour lire ou modifier les attributs de la classes on utilise des accesseurs (getter en anglais) et des mutateurs (setter dans la langue de Shakespeare). Les accesseurs et mutateurs ne sont rien d'autres que des méthodes.
* Le mot-clé `public` avant les méthodes indique que ces dernières peuvent être appelé dans une autre partie du code (programme principale par exemple).
* Les méthodes sont comme les fonctions, elles ont un type de retour, ici *void* ! Dans notre cas, nos méthodes ne retournant aucune valeur.
* Vous avez sûrement remarqué qu'il y a une méthode particulière qui a le même nom que notre classe. Il s'agit d'un constructeur. Quand vous utilisez une classe, il faut l'instancier, créer un objet. C'est grâce au constructeur que vous allez réaliser l'instanciation.

Passons à la définition.

```cpp
#include "Character.h"

Character::Character() : x(10), y(5) {}

// Ce constructeur est équivalent à :
//  Character::Character() {
//    this->x = 10;
//    this->y = 5;
//  }

void Character::manage() {
  // Note :
  // * Le test : (y > 0) permet de ne pas sortir du haut de l'écran.
  // * Le test : (x < 19) permet de ne pas sortir de la droite de l'écran.
  // * Le test : (y < 9) permet de ne pas sortir du bas de l'écran.
  // * Le test : (x > 0) permet de ne pas sortir de la gauche de l'écran.
  // Ainsi on définit les limites du personnage.
  if(gb.buttons.pressed(BUTTON_UP)) {
    if(this->y > 0) {
      this->y--;
    }
  } else if(gb.buttons.pressed(BUTTON_RIGHT)) {
    if(this->x < 19) {
      this->x++;
    }
  } else if(gb.buttons.pressed(BUTTON_DOWN)) {
    if(this->y < 9) {
      this->y++;
    }
  } else if(gb.buttons.pressed(BUTTON_LEFT)) {
    if(this->x > 0) {
      this->x--;
    }
  }
}

void Character::paint() {
  for(int r=0 ; r<=this->y ; r++) {
    for(int c=0; c<20 || c<this->x ; c++) {
      if(c == this->x && r == this->y) {
        gb.display.print("x"); // afficher le personnage
      } else {
        gb.display.print(" "); // afficher une colonne vide
      }
    }
    gb.display.println(); // passage à la ligne suivante
  }
}
```

Quelques précisions :
* Dans la définition d'une classe il faut importer sa déclaration, grâce au mot-clé `include`.
* Le constructeur initalise les attributs de la classe. Le C++ possède un sucre syntaxique qui permet d'initialiser les attributs très simplements comme vous pouvez le voir, dans le commentaire dans le code.
* C'est quoi this ? Il s'agit d'un pointeur sur l'objet courant. Cela permet d'accéder dans la définition de la classe aux différents membres (attributs et méthodes) de cette classe.
* Pourquoi préfixer nos méthodes par `NomDeMaClasse::` ? Il s'agit d'une spécificité du C++, pensez-y sans quoi vous aurrez une erreur de compilation.

Passons au programme principal :

```cpp
#include <Gamebuino-Meta.h>

#include "Character.h"

Character * character;

void setup() {
  // initialiser la gambuino
  gb.begin();

  // instanciation
  character = new Character();
}

void loop() {
  // boucle d'attente
  gb.waitForUpdate();

  // gestion des commandes
  character->manage();

  // effacer l'écran
  gb.display.clear();

  // on dessine le personnage
  character->paint();
}
```

Revenons sur quelques points :
* Comme vous l'avez probablement remarqué, pour pouvoir utiliser une classe il faut l'importer ! Pour ce faire on utilise le même mot-clé utilisé dans la définition (rappelez-vous il s'agit de `include`).
* Pour spécifier qu'une variable est du type de notre classe : il suffit d'utiliser le nom de notre classe suivi de l'astérisque puis du nom de l'objet (qui est une variable).
* Pour l'instanciation, on utilise le mot clé `new` suivi du constructeur.
* Pour appeler une méthode (publique), il faut écrire le nom de notre objet, suivi de `->` puis du nom de notre méthode.

Vous pouvez [télécharger les sources ici](https://github.com/chris-scientist/gb-poo-additional/tree/master/GBSamplePoo).

### Prenons un peu de distance avec cet exemple de POO

L'inconvénient de ce programme c'est que tout est mélangé : l'affichage, la gestion des commandes, etc. C'est là qu'intervient le modèle d'architecture MVC.

## Le modèle d'architecture Modèle Vue Contrôleur

Le MVC permet d'organiser son code !

Il définit différentes couches, aux nombres de trois, qui ont chacunes leurs responsabilité :
* la couche modèle représente les données : soit ici le personnage ;
* la couche vue gère l'affichage ;
* la couche contrôleur permet d'interagir avec les données.

Je ne vais pas m'étandre sur le MVC je vous renvoie à [mon workshop sur Sokoban](https://github.com/chris-scientist/gb-poo) que j'ai développé selon le MVC.

Pour reprendre notre exemple de code, nous allons donc avoir les classes suivantes :
* CharacterModel, la couche modèle, qui ne gère uniquement les coordonnées de notre personnage ;
* CharacterView, la couche vue, qui aura comme seul responsabilité d'afficher notre personnage ;
* CharacterController, la couche contrôleur, qui en fonction de vos actions sur la console intéragira sur la couche modèle et fera donc évoluer l'affichage (grâce à la couche vue).

Vous trouverez [le code ici](https://github.com/chris-scientist/gb-sample/archive/v2.0.zip).

## Le mot de la fin

Notre programme est simple ici ! Imaginez maintenant que vous ayez à développer un jeu plus complexe comme [les tours de Hanoï](https://github.com/chris-scientist/gb-hanoi) ou encore un [rubik's cube](https://github.com/chris-scientist/gb-rubiks-cube). Une bonne organisation de votre programme vous permettra de le faire évoluer plus simplement. Si vous partagez votre code, un développeur tier appréciera un code clair, qui utilise une architecture éprouvée comme le MVC.
