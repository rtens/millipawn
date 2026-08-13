#include <string>
#include <vector>

#include "./Game.h"

class Puzzle {
 private:
	Game* game;
	vector<Move> steps;
	int step = 0;

 public:
	static const int WRONG = 0;
	static const int RIGHT = 1;
	static const int SOLVED = 2;

	Puzzle(Game* game);
	void start(string pgn, vector<string> solution);
	int propose(Move move);
	void undo();
	Move hint();
	Move last;
};
