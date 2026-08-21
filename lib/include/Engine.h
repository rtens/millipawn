#pragma once

#include "Game.h"

class Engine {
 public:
  Engine(Game* game);
  Move respond();

 private:
  Game* game;
};