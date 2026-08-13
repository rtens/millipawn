#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#include "../lib/include/Game.h"
#include "../test/base.h"

void readFen();
void readPgn();
void moving();
void pawnMoves();
void knightMoves();
void bishopMoves();
void rookMoves();
void queenMoves();
void kingMoves();
void castling();
void enPassant();
void undo();
void illegalMoves();
void gameOver();
void puzzle();

int main() {
	readFen();
	readPgn();
	moving();
	pawnMoves();
	knightMoves();
	bishopMoves();
	rookMoves();
	queenMoves();
	kingMoves();
	castling();
	enPassant();
	undo();
	illegalMoves();
	gameOver();
	puzzle();

	cout << endl;
}
