#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Game.h"
using namespace std;

vector<Move> Game::moves(uint8_t square) {
	vector<Move> moves;
	addMoves(square, moves);

	vector<Move> legals;
	for (Move m : moves) {
		if (isLegal(m)) {
			legals.push_back(m);
		}
	}
	return legals;
}

vector<Move> Game::moves() {
	vector<Move> moves;
	for (uint8_t i = 0; i < 64; i++) {
		if (pieces[i] & turn) {
			addMoves(i, moves);
		}
	}

	vector<Move> legals;
	for (Move m : moves) {
		if (isLegal(m)) {
			legals.push_back(m);
		}
	}
	return legals;
}

bool Game::isLegal(Move m) {
	uint8_t mine = turn;
	make(m);
	bool check = checked(mine);
	undo();
	return !check;
}

bool Game::checked(uint8_t color) {
	for (Move a : attacked(color)) {
		if (pieces[a.to] == (KING | color)) {
			return true;
		}
	}
	return false;
}

void Game::addMoves(uint8_t square, vector<Move>& moves) {
	uint8_t type = pieces[square] & TYPE;
	if (type == PAWN) pawnMoves(square, moves);
	if (type == KNIGHT) knightMoves(square, moves);
	if (type == BISHOP) bishopMoves(square, moves);
	if (type == ROOK) rookMoves(square, moves);
	if (type == QUEEN) queenMoves(square, moves);
	if (type == KING) kingMoves(square, moves);
}

void Game::pawnMoves(uint8_t square, vector<Move>& moves) {
	uint8_t piece = pieces[square];

	int8_t step = 1;
	uint8_t startRow = 1;
	if (piece & WHITE) {
		step = -1;
		startRow = 6;
	}

	addPawnMove(square, moves, step, 0, false);

	uint8_t row = square / 8;
	uint8_t one = square + step * 8;
	if (row == startRow && pieces[one] == EMPTY) {
		addPawnMove(square, moves, step * 2, 0, false);
	}

	for (int8_t d : {-1, 1}) {
		uint8_t to = square + step * 8 + d;
		if (pieces[to] != EMPTY || to == enPassant) {
			addPawnMove(square, moves, step, d);
		}
	}
}

void Game::addPawnMove(uint8_t from, vector<Move>& moves, uint8_t r, uint8_t c,
											 bool capture) {
	uint8_t row = from / 8 + r;
	if (row == 0 || row == 7) {
		addJump(from, moves, r, c, capture, Game::QUEEN);
		addJump(from, moves, r, c, capture, Game::ROOK);
		addJump(from, moves, r, c, capture, Game::KNIGHT);
		addJump(from, moves, r, c, capture, Game::BISHOP);
	} else {
		addJump(from, moves, r, c, capture);
	}
}

void Game::knightMoves(uint8_t square, vector<Move>& moves) {
	addJump(square, moves, -2, -1);
	addJump(square, moves, -2, 1);
	addJump(square, moves, -1, -2);
	addJump(square, moves, -1, 2);
	addJump(square, moves, 1, -2);
	addJump(square, moves, 1, 2);
	addJump(square, moves, 2, -1);
	addJump(square, moves, 2, 1);
}

void Game::bishopMoves(uint8_t square, vector<Move>& moves) {
	addSlide(square, moves, -1, -1);
	addSlide(square, moves, -1, 1);
	addSlide(square, moves, 1, -1);
	addSlide(square, moves, 1, 1);
}

void Game::rookMoves(uint8_t square, vector<Move>& moves) {
	addSlide(square, moves, -1, 0);
	addSlide(square, moves, 0, -1);
	addSlide(square, moves, 0, 1);
	addSlide(square, moves, 1, 0);
}

void Game::queenMoves(uint8_t square, vector<Move>& moves) {
	rookMoves(square, moves);
	bishopMoves(square, moves);
}

void Game::kingMoves(uint8_t square, vector<Move>& moves) {
	addJump(square, moves, -1, -1);
	addJump(square, moves, -1, 0);
	addJump(square, moves, -1, 1);
	addJump(square, moves, 0, -1);
	addJump(square, moves, 0, 1);
	addJump(square, moves, 1, -1);
	addJump(square, moves, 1, 0);
	addJump(square, moves, 1, 1);

	if (square == 60) {
		if (canCastle(WHITE, KING)) {
			addJump(square, moves, 0, 2);
		}
		if (canCastle(WHITE, QUEEN)) {
			addJump(square, moves, 0, -2);
		}
	}

	if (square == 4) {
		if (canCastle(BLACK, KING)) {
			addJump(square, moves, 0, 2);
		}
		if (canCastle(BLACK, QUEEN)) {
			addJump(square, moves, 0, -2);
		}
	}
}

bool Game::canCastle(uint8_t color, uint8_t side) {
	uint8_t castle = castleBlack;
	uint8_t king = 4;
	if (color == WHITE) {
		castle = castleWhite;
		king = 60;
	}

	if (!(castle & side)) return false;

	vector<uint8_t> gap = {};
	if (side == QUEEN) {
		gap = {
				static_cast<uint8_t>(king - 1),
				static_cast<uint8_t>(king - 2),
				static_cast<uint8_t>(king - 3),
		};
	} else {
		gap = {
				static_cast<uint8_t>(king + 1),
				static_cast<uint8_t>(king + 2),
		};
	}

	for (uint8_t g : gap) {
		if (pieces[g] != EMPTY) return false;
	}

	for (Move a : attacked(color)) {
		if (a.to == king) return false;
		if (a.to == gap[0]) return false;
	}

	return true;
}

vector<Move> Game::attacked(uint8_t color) {
	vector<Move> attacks;

	for (uint8_t i = 0; i < 64; i++) {
		if (castleBlack && i == 4) continue;
		if (castleWhite && i == 60) continue;

		uint8_t attacker = pieces[i];
		if (!attacker) continue;
		if (attacker & color) continue;

		addMoves(i, attacks);

		if (attacker == (WHITE | PAWN) && i / 8 == 1) {
			attacks.push_back(Move{i, static_cast<uint8_t>(i - 7)});
			attacks.push_back(Move{i, static_cast<uint8_t>(i - 9)});
		}
		if (attacker == (BLACK | PAWN) && i / 8 == 6) {
			attacks.push_back(Move{i, static_cast<uint8_t>(i + 7)});
			attacks.push_back(Move{i, static_cast<uint8_t>(i + 9)});
		}
	}

	return attacks;
}

void Game::addSlide(uint8_t from, vector<Move>& moves, int8_t r, int8_t c) {
	for (uint8_t i = 1; i < 8; i++) {
		if (!addJump(from, moves, r * i, c * i)) {
			return;
		}
	}
}

bool Game::addJump(uint8_t from, vector<Move>& moves, int8_t r, int8_t c,
									 bool capture, uint8_t promote) {
	uint8_t row = from / 8 + r;
	if (row < 0 || row > 7) return false;
	uint8_t col = from % 8 + c;
	if (col < 0 || col > 7) return false;

	uint8_t to = row * 8 + col;
	if ((pieces[to] & COLOR) == (pieces[from] & COLOR)) return false;

	if (pieces[to]) {
		if (capture) {
			moves.push_back(Move{from, to, promote});
		}
		return false;
	}

	moves.push_back(Move{from, to, promote});
	return true;
}
