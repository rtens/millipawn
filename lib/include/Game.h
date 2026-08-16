// #pragma once

// #include <string>
// #include <vector>
// using namespace std;

// namespace Chess {

// class Game {
//  public:
// 	enum Result { CHECKMATE, STALEMATE };

// 	int isOver();
// 	vector<Move> moves(int square);
// 	vector<Move> moves();
// 	void reset();

//  private:
// 	vector<Move> attacked(int color);
// 	bool canCastle(int color, int side);
// 	bool isLegal(Move move);
// 	bool checked(int color);
// 	void addMoves(int square, vector<Move>& moves);
// 	void pawnMoves(int square, vector<Move>& moves);
// 	void knightMoves(int square, vector<Move>& moves);
// 	void bishopMoves(int square, vector<Move>& moves);
// 	void rookMoves(int square, vector<Move>& moves);
// 	void queenMoves(int square, vector<Move>& moves);
// 	void kingMoves(int square, vector<Move>& moves);
// 	void addPawnMove(int square, vector<Move>& moves, int r, int c,
// 									 bool capture = true);
// 	bool addJump(int from, vector<Move>& moves, int r, int c, bool capture =
// true, 							 int promote = 0); 	void addSlide(int from, vector<Move>& moves, int r,
// int c);
// };

// }	 // namespace Chess