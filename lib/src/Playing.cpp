#include "../include/Game.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const string Game::STARTPOS =
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";

void Game::make(Move move) {
	if (move.promote) {
		pieces[move.to] = move.promote | (pieces[move.from] & COLOR);
	} else {
		pieces[move.to] = pieces[move.from];
	}
	pieces[move.from] = EMPTY;
	turn ^= BLACK | WHITE;
}
