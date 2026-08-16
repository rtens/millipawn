#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Game.h"
using namespace std;

vector<Move> Game::moves(int square) {
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
	for (int i = 0; i < 64; i++) {
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
	int mine = turn;
	make(m);
	bool check = checked(mine);
	undo();
	return !check;
}

bool Game::checked(int color) {
	for (Move a : attacked(color)) {
		if (pieces[a.to] == (KING | color)) {
			return true;
		}
	}
	return false;
}

void Game::addMoves(int square, vector<Move>& moves) {
	int type = pieces[square] & TYPE;
	if (type == PAWN) pawnMoves(square, moves);
	if (type == KNIGHT) knightMoves(square, moves);
	if (type == BISHOP) bishopMoves(square, moves);
	if (type == ROOK) rookMoves(square, moves);
	if (type == QUEEN) queenMoves(square, moves);
	if (type == KING) kingMoves(square, moves);
}

void Game::pawnMoves(int square, vector<Move>& moves) {
	int piece = pieces[square];

	int step = 1;
	int startRow = 1;
	if (piece & WHITE) {
		step = -1;
		startRow = 6;
	}

	addPawnMove(square, moves, step, 0, false);

	int row = square / 8;
	int one = square + step * 8;
	if (row == startRow && pieces[one] == EMPTY) {
		addPawnMove(square, moves, step * 2, 0, false);
	}

	for (int d : {-1, 1}) {
		int to = square + step * 8 + d;
		if (pieces[to] != EMPTY || to == enPassant) {
			addPawnMove(square, moves, step, d);
		}
	}
}

void Game::addPawnMove(int from, vector<Move>& moves, int r, int c,
											 bool capture) {
	int row = from / 8 + r;
	if (row == 0 || row == 7) {
		addJump(from, moves, r, c, capture, Game::QUEEN);
		addJump(from, moves, r, c, capture, Game::ROOK);
		addJump(from, moves, r, c, capture, Game::KNIGHT);
		addJump(from, moves, r, c, capture, Game::BISHOP);
	} else {
		addJump(from, moves, r, c, capture);
	}
}

void Game::knightMoves(int square, vector<Move>& moves) {
	addJump(square, moves, -2, -1);
	addJump(square, moves, -2, 1);
	addJump(square, moves, -1, -2);
	addJump(square, moves, -1, 2);
	addJump(square, moves, 1, -2);
	addJump(square, moves, 1, 2);
	addJump(square, moves, 2, -1);
	addJump(square, moves, 2, 1);
}

void Game::bishopMoves(int square, vector<Move>& moves) {
	addSlide(square, moves, -1, -1);
	addSlide(square, moves, -1, 1);
	addSlide(square, moves, 1, -1);
	addSlide(square, moves, 1, 1);
}

void Game::rookMoves(int square, vector<Move>& moves) {
	addSlide(square, moves, -1, 0);
	addSlide(square, moves, 0, -1);
	addSlide(square, moves, 0, 1);
	addSlide(square, moves, 1, 0);
}

void Game::queenMoves(int square, vector<Move>& moves) {
	rookMoves(square, moves);
	bishopMoves(square, moves);
}

void Game::kingMoves(int square, vector<Move>& moves) {
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

bool Game::canCastle(int color, int side) {
	int castle = castleBlack;
	int king = 4;
	if (color == WHITE) {
		castle = castleWhite;
		king = 60;
	}

	if (!(castle & side)) return false;

	vector<int> gap = {};
	if (side == QUEEN) {
		gap = {king - 1, king - 2, king - 3};
	} else {
		gap = {king + 1, king + 2};
	}

	for (int g : gap) {
		if (pieces[g] != EMPTY) return false;
	}

	for (Move a : attacked(color)) {
		if (a.to == king) return false;
		if (a.to == gap[0]) return false;
	}

	return true;
}

vector<Move> Game::attacked(int color) {
	vector<Move> attacks;

	for (int i = 0; i < 64; i++) {
		if (castleBlack && i == 4) continue;
		if (castleWhite && i == 60) continue;

		int attacker = pieces[i];
		if (attacker && !(attacker & color)) {
			addMoves(i, attacks);
		}
	}

	return attacks;
}

void Game::addSlide(int from, vector<Move>& moves, int r, int c) {
	for (int i = 1; i < 8; i++) {
		if (!addJump(from, moves, r * i, c * i)) {
			return;
		}
	}
}

bool Game::addJump(int from, vector<Move>& moves, int r, int c, bool capture,
									 int promote) {
	int row = from / 8 + r;
	if (row < 0 || row > 7) return false;
	int col = from % 8 + c;
	if (col < 0 || col > 7) return false;

	int to = row * 8 + col;
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
