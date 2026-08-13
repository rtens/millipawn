#include "../include/Puzzle.h"

#include <iostream>
#include <string>
#include <vector>

#include "../include/Game.h"

Puzzle::Puzzle(Game* g) { game = g; }

void Puzzle::start(string pgn, vector<string> solution) {
	game->start();
	game->apply(pgn);

	step = 0;
	steps = {};
	for (string s : solution) {
		int from = Game::toSquare(s.substr(0, 2));
		int to = Game::toSquare(s.substr(2));
		steps.push_back(Move{from, to});
	}
}

int Puzzle::propose(Move move) {
	if (step == steps.size()) {
		return SOLVED;
	}

	game->make(move);
	last = move;

	Move next = steps[step];
	step++;

	if (move.from != next.from || move.to != next.to) {
		return WRONG;
	}

	if (step == steps.size()) {
		return SOLVED;
	}

	next = steps[step];
	step++;

	game->make(next);
	last = next;

	return RIGHT;
}

void Puzzle::undo() {
	if (!step) return;
	last = Move{};
	game->undo();
	step--;
}

Move Puzzle::hint() { return steps[step]; }
