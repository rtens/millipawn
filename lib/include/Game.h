#pragma once

#include <cstdint>
#include <string>
#include <vector>
using namespace std;

struct Move {
	uint8_t from = 255;
	uint8_t to = 255;
	uint8_t promote = 0;
};

struct MadeMove {
	uint8_t from = 255;
	uint8_t to = 255;
	uint8_t capture = 0;
	uint8_t promoted = 0;
	uint8_t enPassant = 255;
	uint8_t castledBlack = 0;
	uint8_t castledWhite = 0;
};

class Game {
 private:
	// Playing
	vector<MadeMove> history{};

	// Move Generation
	uint8_t castleWhite = QUEEN | KING;
	uint8_t castleBlack = QUEEN | KING;
	uint8_t enPassant = NOWHERE;
	bool canCastle(uint8_t color, uint8_t side);
	vector<Move> attacked(uint8_t color);
	bool isLegal(Move move);
	bool checked(uint8_t color);
	void addMoves(uint8_t square, vector<Move>& moves);
	void pawnMoves(uint8_t square, vector<Move>& moves);
	void knightMoves(uint8_t square, vector<Move>& moves);
	void bishopMoves(uint8_t square, vector<Move>& moves);
	void rookMoves(uint8_t square, vector<Move>& moves);
	void queenMoves(uint8_t square, vector<Move>& moves);
	void kingMoves(uint8_t square, vector<Move>& moves);
	void addPawnMove(uint8_t square, vector<Move>& moves, uint8_t r, uint8_t c,
									 bool capture = true);
	bool addJump(uint8_t from, vector<Move>& moves, int r, int c,
							 bool capture = true, uint8_t promote = 0);
	void addSlide(uint8_t from, vector<Move>& moves, int r, int c);

 public:
	static const uint8_t TYPE = 7;
	static const uint8_t COLOR = 24;
	static const uint8_t EMPTY = 0;
	static const uint8_t NOWHERE = 255;

	static const uint8_t KING = 1;
	static const uint8_t QUEEN = 2;
	static const uint8_t BISHOP = 3;
	static const uint8_t KNIGHT = 4;
	static const uint8_t ROOK = 5;
	static const uint8_t PAWN = 6;

	static const uint8_t WHITE = 8;
	static const uint8_t BLACK = 16;

	static const uint8_t CHECKMATE = 1;
	static const uint8_t STALEMATE = 2;

	uint8_t turn = WHITE;
	uint8_t pieces[64] = {};

	// Playing
	static const string STARTPOS;
	void make(Move move);
	void undo();
	uint8_t isOver();

	// Move Generation
	vector<Move> moves(uint8_t square);
	vector<Move> moves();

	// Serialization
	void start(string fen = STARTPOS);
	void apply(string pgn);
	string fen();
	static string print(Move move);
	static string print(uint8_t square);
	static uint8_t toSquare(string s);
};