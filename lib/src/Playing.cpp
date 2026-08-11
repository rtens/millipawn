#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Game.h"
using namespace std;

const string Game::STARTPOS =
		"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

void Game::make(Move move) {
	int piece = pieces[move.from];

	// Move & Capture
	MadeMove made = MadeMove{move.from, move.to, pieces[move.to]};
	history.push_back(made);
	pieces[move.to] = piece;
	pieces[move.from] = EMPTY;

	// Promotion
	if (move.promote) {
		pieces[move.to] = move.promote | (piece & COLOR);
	}

	// Capture en passant
	if (move.to == enPassant) {
		if (piece & WHITE) {
			pieces[move.to + 8] = 0;
		} else {
			pieces[move.to - 8] = 0;
		}
	}

	// Set en passant flag
	enPassant = -1;
	if (piece & PAWN) {
		int start = 1;
		int step = 8;
		if (piece & WHITE) {
			start = 6;
			step = -8;
		}
		int row = move.from / 8;
		if (row == start && move.to == move.from + 2 * step) {
			enPassant = move.from + step;
		}
	}

	// Castling
	if (move.from == 60) {
		if ((castleWhite & KING) && move.to == 62) {
			pieces[61] = pieces[63];
			pieces[63] = EMPTY;
		}
		if ((castleWhite & QUEEN) && move.to == 58) {
			pieces[59] = pieces[56];
			pieces[56] = EMPTY;
		}
		castleWhite = 0;
	}
	if (move.from == 4) {
		if ((castleBlack & KING) && move.to == 6) {
			pieces[5] = pieces[7];
			pieces[7] = EMPTY;
		}
		if ((castleBlack & QUEEN) && move.to == 2) {
			pieces[3] = pieces[0];
			pieces[0] = EMPTY;
		}
		castleBlack = 0;
	}
	if (move.from == 0 || move.to == 0) {
		castleBlack &= ~QUEEN;
	}
	if (move.from == 7 || move.to == 7) {
		castleBlack &= ~KING;
	}
	if (move.from == 56 || move.to == 56) {
		castleWhite &= ~QUEEN;
	}
	if (move.from == 63 || move.to == 63) {
		castleWhite &= ~KING;
	}

	// Next turn
	turn ^= COLOR;
}

void Game::undo() {
	if (!history.size()) return;

	MadeMove move = history.back();
	history.pop_back();

	// Move
	pieces[move.from] = pieces[move.to];
	pieces[move.to] = move.capture;

	// Previous turn
	turn ^= COLOR;
}