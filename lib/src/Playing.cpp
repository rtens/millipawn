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
			pieces[61] = pieces[63];
			pieces[63] = EMPTY;
		} else if (move.to == 58) {
			pieces[59] = pieces[56];
			pieces[56] = EMPTY;
		}
	} else if (move.from == 4) {
		if (move.to == 6) {
			pieces[5] = pieces[7];
			pieces[7] = EMPTY;
		} else if (move.to == 2) {
			pieces[3] = pieces[0];
			pieces[0] = EMPTY;
		}
	}

	turn ^= BLACK | WHITE;
}
