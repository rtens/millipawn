#include "../include/Engine.h"

#include <cstdlib>
#include <ctime>
using namespace std;

Engine::Engine(Game* g) { game = g; }

Move Engine::respond() {
  auto moves = game->moves();
  srand(time(0));
  return moves[rand() % moves.size()];
}