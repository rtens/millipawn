#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Game.h"
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

	if (move.from == 60) {
		if (move.to == 62) {
			make(Move{63, 61});
		} else if (move.to == 58) {
			make(Move{56, 59});
		}
	} else if (move.from == 4) {
		if (move.to == 6) {
			make(Move{7, 5});
		} else if (move.to == 2) {
			make(Move{0, 3});
		}
	}

	turn ^= BLACK | WHITE;
}
