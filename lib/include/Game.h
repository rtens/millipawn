#pragma once

#include <string>
#include <vector>
using namespace std;

struct Move {
	int from = -1;
	int to = -1;
	int promote = 0;
};

class Game {
 private:
	void pawnMoves(int square, vector<Move>& moves);
	void knightMoves(int square, vector<Move>& moves);
	void addPawnMove(int square, vector<Move>& moves, int r, int c, bool capture = true);
	void addJump(int from, vector<Move>& moves, int r, int c, bool capture = true, int promote = 0);

 public:
	static const int TYPE = 7;
	static const int COLOR = 24;
	static const int EMPTY = 0;

	static const int PAWN = 1;
	static const int BISHOP = 2;
	static const int KNIGHT = 3;
	static const int ROOK = 4;
	static const int KING = 5;
	static const int QUEEN = 6;

	static const int WHITE = 8;
	static const int BLACK = 16;

	static const string STARTPOS;

	static string print(Move move);

	int turn = WHITE;
	int pieces[64] = {};

	string fen();
	void restore(string fen);
	void make(Move move);
	void moves(int square, vector<Move>& moves);
};
