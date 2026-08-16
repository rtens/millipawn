#include <string>
#include <vector>
using namespace std;

#include "Piece.h"
using namespace Chess::Piece;

namespace Chess {

struct Move {
	int from = -1;
	int to = -1;
	int promote = 0;
};

class Board {
 public:
	struct State {
		int castleWhite = QUEEN | KING;
		int castleBlack = QUEEN | KING;
		int enPassant = -1;
	};

	static const string STARTPOS;

	int pieces[64] = {};
	int turn = Piece::WHITE;
	State state;

	void make(Move move);
	void undo();

 private:
	struct Made {
		Move move;
		int capture = 0;
		State state;
	};

	vector<Made> history{};
};

}	 // namespace Chess
