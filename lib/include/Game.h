#pragma once

#include <string>
#include <vector>
using namespace std;

struct Move {
	int from = -1;
	int to = -1;
	int promote = 0;
};

struct MadeMove {
	int from = -1;
	int to = -1;
	int capture = 0;
	int promoted = 0;
	int enPassant = -1;
	int castledBlack = 0;
	int castledWhite = 0;
};

class Game {
 private:
	// Playing
	vector<MadeMove> history{};

	// Move Generation
	int castleWhite = QUEEN | KING;
	int castleBlack = QUEEN | KING;
	int enPassant = -1;
	bool canCastle(int color, int side);
	vector<Move> attacked(int color);
	bool isLegal(Move move);
	bool checked(int color);
	void addMoves(int square, vector<Move>& moves);
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

	static const int KING = 1;
	static const int QUEEN = 2;
	static const int BISHOP = 3;
	static const int KNIGHT = 4;
	static const int ROOK = 5;
	static const int PAWN = 6;

	static const int WHITE = 8;
	static const int BLACK = 16;

	static const int CHECKMATE = 1;
	static const int STALEMATE = 2;

	int turn = WHITE;
	int pieces[64] = {};

	// Playing
	static const string STARTPOS;
	void make(Move move);
	void undo();
	int isOver();

	// Move Generation
	vector<Move> moves(int square);
	vector<Move> moves();

	// Serialization
	void start(string fen = STARTPOS);
	void apply(string pgn);
	string fen();
	static string print(Move move);
	static int toSquare(string s);
};
