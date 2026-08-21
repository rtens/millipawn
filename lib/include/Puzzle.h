#include <string>
#include <vector>

#include "./Game.h"

class Puzzle {
 public:
	static const uint8_t WRONG = 0;
	static const uint8_t RIGHT = 1;
	static const uint8_t SOLVED = 2;

	Puzzle(Game* game);
	void start(string pgn, vector<string> solution);
	uint8_t propose(Move move);
	void respond();
	void undo();
	Move hint();
	Move last;

 private:
	Game* game;
	vector<Move> steps;
	uint8_t step = 0;
};
