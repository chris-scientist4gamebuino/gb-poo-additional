// author: chris-scientist
// created at: 14/08/2020

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
