#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#include "../lib/include/Game.h"

void should(string actual, string expected, string tag = "Failed")
{
	if (actual != expected)
		throw "[" + tag + "] Expected \n  " + expected + "\ngot\n  " + actual;
}

void should(int a, int e, string tag = "Failed") {
	should(to_string(a), to_string(e), tag);
}

void test(string name, function<void()> func)
{
	try
	{
		func();
		cout << ".";
	}
	catch (const string &e)
	{
		cout << endl
				 << name << ": " << e << endl;
	}
}

void restoring() {
	test("empty board", []() {
		Game g;
		should(g.turn, Game::WHITE);
		should(g.fen(), "8/8/8/8/8/8/8/8 w - - 0 1");
	});

	test("starting position", []() {
		Game g;
		g.restore(Game::STARTPOS);
		should(g.turn, Game::WHITE);
		should(g.fen(), Game::STARTPOS);
	});

	test("mixed position", []() {
		Game g;
		string mixed = "3r2B1/p3pp2/5Q2/kN3RpP/3P2P1/6P1/2PP2PP/7K w - - 0 1";
		g.restore(mixed);
		should(g.fen(), mixed);
	});

	test("overwrite pieces", []() {
		Game g;
		g.restore("8/8/8/8/8/8/8/P7 w - - 0 1");
		g.restore("8/8/8/8/8/8/P7/8 w - - 0 1");
		should(g.fen(), "8/8/8/8/8/8/P7/8 w - - 0 1");
	});
}

void moving() {
	test("blacks turn", []() {
		Game g;
		g.restore("8/8/8/8/8/8/8/8 b - - 0 1");
		should(g.turn, Game::BLACK);
		should(g.fen(), "8/8/8/8/8/8/8/8 b - - 0 1");
	});

	test("simple move", []() {
		Game g;
		g.restore("8/8/8/8/8/8/8/7P w - - 0 1");
		g.make(Move{63, 63 - 16});
		should(g.turn, Game::BLACK);
		should(g.fen(), "8/8/8/8/8/7P/8/8 b - - 0 1");
	});
}

string printMoves(vector<Move> moves)
{
	return accumulate(moves.begin(), moves.end(), string(),
										[](const string &s, Move m)
										{ return s + "," + Game::print(m); });
}

void pawnMoves()
{
	test("start moves", []() {
		Game g;
		g.restore("8/p7/8/8/8/8/P7/8 w - - 0 1");
		auto moves = printMoves(g.moves(48));
		should(moves, ",a2a3,a2a4");
		moves = printMoves(g.moves(8));
		should(moves, ",a7a6,a7a5");
	});

	test("normal move", []() {
		Game g;
		g.restore("8/8/p7/8/8/P7/8/8 w - - 0 1");
		auto moves = printMoves(g.moves(40));
		should(moves, ",a3a4");
		moves = printMoves(g.moves(16));
		should(moves, ",a6a5");
	});

	test("blocked", []() {
		Game g;
		g.restore("8/8/8/8/PP6/P7/PP6/8");

		auto moves = printMoves(g.moves(48));
		should(moves, "");

		moves = printMoves(g.moves(40));
		should(moves, "");

		moves = printMoves(g.moves(49));
		should(moves, ",b2b3");
	});
}

int main() {
	restoring();
	moving();
	pawnMoves();
}
