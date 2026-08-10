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
	// Move Generation
	void pawnMoves(int square, vector<Move>& moves);
	void knightMoves(int square, vector<Move>& moves);
	void bishopMoves(int square, vector<Move>& moves);
	void rookMoves(int square, vector<Move>& moves);
	void queenMoves(int square, vector<Move>& moves);
	void kingMoves(int square, vector<Move>& moves);
	void addPawnMove(int square, vector<Move>& moves, int r, int c,
									 bool capture = true);
	bool addJump(int from, vector<Move>& moves, int r, int c, bool capture = true,
							 int promote = 0);
	void addSlide(int from, vector<Move>& moves, int r, int c);

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

	int turn = WHITE;
	int pieces[64] = {};

	// Playing
	static const string STARTPOS;
	void make(Move move);

	// Move Generation
	void moves(int square, vector<Move>& moves);

	// Serialization
	string fen();
	void restore(string fen);
	static string print(Move move);
};
