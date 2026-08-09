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

void Game::moves(int square, vector<Move>& moves) {
	int type = pieces[square] & TYPE;
	if (type == PAWN) pawnMoves(square, moves);
	if (type == KNIGHT) knightMoves(square, moves);
}

void addPawnMove(vector<Move>& moves, int piece, int from, int by) {
	int to = from + by;
	if ((to / 8) % 7 == 0) {
		moves.push_back(Move{from, to, Game::QUEEN});
		moves.push_back(Move{from, to, Game::ROOK});
		moves.push_back(Move{from, to, Game::KNIGHT});
		moves.push_back(Move{from, to, Game::BISHOP});
	} else {
		moves.push_back(Move{from, to});
	}
}

void Game::pawnMoves(int square, vector<Move>& moves) {
	int piece = pieces[square];

	int dir = 1;
	int startRow = 1;
	if (piece & WHITE) {
		dir = -1;
		startRow = 6;
	}

	int one_step = 8 * dir;
	int two_steps = one_step * 2;
	int diag_left = one_step - 1;
	int diag_right = one_step + 1;

	if (pieces[square + one_step] == EMPTY) {
		addPawnMove(moves, piece, square, one_step);

		if (square / 8 == startRow && pieces[square + two_steps] == EMPTY) {
			addPawnMove(moves, piece, square, two_steps);
		}
	}

	vector<int> diags;
	if (square % 8 != 0) diags.push_back(diag_left);
	if (square % 8 != 7) diags.push_back(diag_right);

	for (int d : diags) {
		int target = pieces[square + d];
		if (target != EMPTY && (target & COLOR) != (piece & COLOR)) {
			addPawnMove(moves, piece, square, d);
		}
	}
}

void Game::knightMoves(int square, vector<Move>& moves) {
	for (int by : {-17, -15, -10, -6, 6, 10, 15, 17}) {
		moves.push_back(Move{square, square + by});
	}
}

string Game::print(Move move) {
	stringstream ss;

	ss << char((move.from % 8) + 'a') << 8 - (move.from / 8);
	ss << char((move.to % 8) + 'a') << 8 - (move.to / 8);

	if (move.promote) {
		if (move.promote == PAWN) ss << 'p';
		if (move.promote == ROOK) ss << 'r';
		if (move.promote == KNIGHT) ss << 'n';
		if (move.promote == BISHOP) ss << 'b';
		if (move.promote == QUEEN) ss << 'q';
		if (move.promote == KING) ss << 'k';
	}

	return ss.str();
}

string Game::fen() {
	stringstream ss;

	int empties = 0;
	for (int i = 0; i < 64; i++) {
		if (i > 0 && i % 8 == 0) {
			if (empties) {
				ss << empties;
				empties = 0;
			}
			ss << "/";
		}

		int p = pieces[i];
		if (p == EMPTY) {
			empties++;

		} else {
			if (empties) {
				ss << to_string(empties);
				empties = 0;
			}

			int type = p & TYPE;
			int color = p & COLOR;
			char c = '?';

			if (type == PAWN) c = 'p';
			if (type == ROOK) c = 'r';
			if (type == KNIGHT) c = 'n';
			if (type == BISHOP) c = 'b';
			if (type == QUEEN) c = 'q';
			if (type == KING) c = 'k';

			if (color == WHITE) c = c - 'a' + 'A';

			ss << c;
		}
	}

	if (empties) {
		ss << empties;
	}

	if (turn == WHITE) {
		ss << " w";
	} else {
		ss << " b";
	}

	ss << " - - 0 1";
	return ss.str();
}

void Game::restore(string fen) {
	const int p_pieces = 0;
	const int p_turn = 1;
	const int p_castle = 2;
	const int p_enpassant = 3;
	int part = p_pieces;

	int row = 0;
	int col = 0;

	for (int i = 0; i < fen.length(); i++) {
		char c = fen[i];

		if (c == ' ') {
			part++;
		}

		switch (part) {
			case p_pieces:
				if (c == '/') {
					row++;
					col = 0;

				} else if (c >= '1' && c <= '8') {
					for (int i = 0; i < c - '0'; i++) {
						pieces[row * 8 + col] = EMPTY;
						col++;
					}

				} else {
					int color = WHITE;
					if (c > 'a') {
						color = BLACK;
						c = c - 'a' + 'A';
					}

					int type;
					if (c == 'P') type = PAWN;
					if (c == 'R') type = ROOK;
					if (c == 'N') type = KNIGHT;
					if (c == 'B') type = BISHOP;
					if (c == 'Q') type = QUEEN;
					if (c == 'K') type = KING;

					pieces[row * 8 + col] = color | type;
					col++;
				}
				break;

			case p_turn:
				turn = WHITE;
				if (c == 'b') turn = BLACK;
				break;
		}
	}
}
