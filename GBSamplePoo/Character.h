// author: chris-scientist
// created at: 14/08/2020

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
