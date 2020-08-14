// author: chris-scientist
// created at: 14/08/2020

#include "Character.h"

Character::Character() : x(10), y(5) {}

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
