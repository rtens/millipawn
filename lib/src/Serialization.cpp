#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Game.h"
using namespace std;

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

	ss << " ";
	if (!castleWhite && !castleBlack) {
		ss << "-";
	} else {
		if (castleWhite & KING) {
			ss << "K";
		}
		if (castleWhite & QUEEN) {
			ss << "Q";
		}
		if (castleBlack & KING) {
			ss << "k";
		}
		if (castleBlack & QUEEN) {
			ss << "q";
		}
	}

	ss << " - 0 1";
	return ss.str();
}

void Game::restore(string fen) {
	for (int i = 0; i < 64; i++) {
		pieces[i] = EMPTY;
	}
	castleBlack = 0;
	castleWhite = 0;

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

			case p_castle:
				if (c == 'K') castleWhite += KING;
				if (c == 'Q') castleWhite += QUEEN;
				if (c == 'k') castleBlack += KING;
				if (c == 'q') castleBlack += QUEEN;
				break;
		}
	}
}
