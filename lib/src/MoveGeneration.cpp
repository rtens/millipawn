#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Game.h"
using namespace std;

vector<Move> Game::moves(int square) {
	vector<Move> moves;
	addMoves(square, moves);
	return moves;
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

	if (square / 8 == startRow && pieces[square + step * 8] == EMPTY) {
		addPawnMove(square, moves, step * 2, 0, false);
	}
	if (pieces[square + step * 8 - 1] != EMPTY) {
		addPawnMove(square, moves, step, -1);
	}
	if (pieces[square + step * 8 + 1] != EMPTY) {
		addPawnMove(square, moves, step, 1);
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

	if (castleWhite && square == 60) {
		if (castleWhite & KING && !pieces[61] && !pieces[62]) {
			addJump(square, moves, 0, 2);
		}
		if (castleWhite & QUEEN && !pieces[59] && !pieces[58]) {
			addJump(square, moves, 0, -2);
		}
	}

	if (castleBlack && square == 4) {
		if (castleBlack & KING && !pieces[5] && !pieces[6]) {
			addJump(square, moves, 0, 2);
		}
		if (castleBlack & QUEEN && !pieces[3] && !pieces[2]) {
			addJump(square, moves, 0, -2);
		}
	}
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
	if (pieces[to] & pieces[from] & COLOR) return false;

	if (pieces[to]) {
		if (capture) {
			moves.push_back(Move{from, to, promote});
		}
		return false;
	}

	moves.push_back(Move{from, to, promote});
	return true;
}
