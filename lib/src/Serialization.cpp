#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/Game.h"
using namespace std;

string Game::print(int square) {
	stringstream ss;
	ss << char(square % 8 + 'a') << 8 - square / 8;
	return ss.str();
}

int Game::toSquare(string s) { return (s[0] - 'a') + (8 - (s[1] - '0')) * 8; }

int toType(char c) {
	if (c == 'P') return Game::PAWN;
	if (c == 'R') return Game::ROOK;
	if (c == 'N') return Game::KNIGHT;
	if (c == 'B') return Game::BISHOP;
	if (c == 'Q') return Game::QUEEN;
	if (c == 'K') return Game::KING;
	return Game::EMPTY;
}

string Game::print(Move move) {
	stringstream ss;

	ss << print(move.from) << print(move.to);

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

	ss << " ";

	if (enPassant > -1) {
		ss << print(enPassant);
	} else {
		ss << "-";
	}

	ss << " 0 1";
	return ss.str();
}

void Game::start(string fen) {
	for (int i = 0; i < 64; i++) {
		pieces[i] = EMPTY;
	}
	castleBlack = 0;
	castleWhite = 0;
	enPassant = -1;

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
			continue;
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

					pieces[row * 8 + col] = color | toType(c);
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

			case p_enpassant:
				if (c == '-') break;
				enPassant = toSquare(string{c, fen[++i]});
				break;
		}
	}
}

void Game::apply(string pgn) {
	stringstream token;

	for (int i = 0; i < pgn.length(); i++) {
		char c = pgn[i];

		if (c == 'x') continue;
		if (c == '=') token << c;
		if (c == '-') token << c;
		if (c >= 'a' && c <= 'z') token << c;
		if (c >= 'A' && c <= 'Z') token << c;
		if (c >= '0' && c <= '9') token << c;

		if (i == pgn.length() - 1 || pgn[i + 1] == ' ') {
			string move = token.str();
			token.str("");
			token.clear();

			if (move.length() < 2) return;

			if (move == "O-O-O") {
				if (turn == WHITE) {
					make(Move{60, 58});
				} else {
					make(Move{4, 2});
				}

			} else if (move == "O-O") {
				if (turn == WHITE) {
					make(Move{60, 62});
				} else {
					make(Move{4, 6});
				}

			} else {
				int promote = 0;
				if (move.length() >= 4 && move[move.length() - 2] == '=') {
					promote = toType(move[move.length() - 1]);
					move = move.substr(0, move.length() - 2);
				}

				int to = toSquare(move.substr(move.length() - 2));
				move = move.substr(0, move.length() - 2);

				int type = PAWN;
				if (move[0] > 'A' && move[0] < 'Z') {
					type = toType(move[0]);
					move = move.substr(1);
				}

				int row = -1;
				int col = -1;
				if (move.length() == 1) {
					if (move[0] >= 'a' && move[0] <= 'h') {
						col = toSquare(move + "1") % 8;
					} else if (move[0] >= '1' && move[0] <= '8') {
						row = toSquare("a" + move) / 8;
					}
				} else if (move.length() == 2) {
					int s = toSquare(move);
					row = s / 8;
					col = s % 8;
				}

				bool found = false;
				for (Move m : moves()) {
					int piece = pieces[m.from];
					if (m.to != to) continue;
					if ((piece & TYPE) != type) continue;
					if (col > -1 && m.from % 8 != col) continue;
					if (row > -1 && m.from / 8 != row) continue;
					if (promote && m.promote != promote) continue;

					make(m);
					found = true;
					break;
				}

				if (!found) {
					return;
				}
			}
		}
	}
}