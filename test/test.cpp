#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#include "../lib/include/Game.h"

void should(string actual, string expected, string tag = "Failed") {
	if (actual != expected)
		throw "[" + tag + "] Expected \n  " + expected + "\ngot\n  " + actual;
}

void should(int a, int e, string tag = "Failed") {
	should(to_string(a), to_string(e), tag);
}

void test(string name, function<void()> func) {
	try {
		func();
		cout << ".";
	} catch (const string& e) {
		cout << endl << name << ": " << e << endl;
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
		g.restore("P w - - 0 1");
		g.restore("8/P w - - 0 1");
		should(g.fen(), "8/P7/8/8/8/8/8/8 w - - 0 1");
	});
}

void moving() {
	test("blacks turn", []() {
		Game g;
		g.restore("/ b - - 0 1");
		should(g.turn, Game::BLACK);
		should(g.fen(), "8/8/8/8/8/8/8/8 b - - 0 1");
	});

	test("simple move", []() {
		Game g;
		g.restore("/P w - - 0 1");
		g.make(Move{8, 20});
		should(g.turn, Game::BLACK);
		should(g.fen(), "8/8/4P3/8/8/8/8/8 b - - 0 1");
	});
}

string pm(Game g, int square) {
	vector<Move> moves{};
	g.moves(square, moves);

	return accumulate(
			moves.begin(), moves.end(), string(),
			[](const string& s, Move m) { return s + "," + Game::print(m); });
}

void pawnMoves() {
	test("start moves", []() {
		Game g;
		g.restore("/p/////P w - - 0 1");

		should(pm(g, (48)), ",a2a3,a2a4");
		should(pm(g, (8)), ",a7a6,a7a5");
	});

	test("normal move", []() {
		Game g;
		g.restore("//p///P// w - - 0 1");

		should(pm(g, (40)), ",a3a4");
		should(pm(g, (16)), ",a6a5");
	});

	test("blocked", []() {
		Game g;
		g.restore("////PP/P/PP");

		should(pm(g, (48)), "");
		should(pm(g, (40)), "");
		should(pm(g, (49)), ",b2b3");
	});

	test("capture", []() {
		Game g;
		g.restore("/2ppp/3P//3p/2PPP");

		should(pm(g, (19)), ",d6c7,d6e7");
		should(pm(g, (35)), ",d4c3,d4e3");
	});

	test("capture on left edge", []() {
		Game g;
		g.restore("7p/pp/P//p6P/PP");
		should(pm(g, (16)), ",a6b7");
		should(pm(g, (32)), ",a4b3");
	});

	test("capture on right edge", []() {
		Game g;
		g.restore("/6pp/p6P//7p/6PP/P");
		should(pm(g, (23)), ",h6g7");
		should(pm(g, (39)), ",h4g3");
	});

	test("white promotes with move", []() {
		Game g;
		g.restore("8/1P");
		should(pm(g, 9), ",b7b8q,b7b8r,b7b8n,b7b8b");

		vector<Move> moves;
		g.moves(9, moves);

		g.make(moves[0]);
		should(g.fen().substr(0, 6), "1Q6/8/");
		g.restore("8/1P");
		g.make(moves[1]);
		should(g.fen().substr(0, 6), "1R6/8/");
		g.restore("8/1P");
		g.make(moves[2]);
		should(g.fen().substr(0, 6), "1N6/8/");
		g.restore("8/1P");
		g.make(moves[3]);
		should(g.fen().substr(0, 6), "1B6/8/");
	});

	test("black promotes with move", []() {
		Game g;
		g.restore("8//////1p/");
		should(pm(g, 49), ",b2b1q,b2b1r,b2b1n,b2b1b");

		vector<Move> moves;
		g.moves(49, moves);

		g.make(moves[0]);
		should(g.fen().substr(11, 6), "/8/1q6");
		g.restore("//////1p/8");
		g.make(moves[1]);
		should(g.fen().substr(11, 6), "/8/1r6");
		g.restore("//////1p/8");
		g.make(moves[2]);
		should(g.fen().substr(11, 6), "/8/1n6");
		g.restore("//////1p/8");
		g.make(moves[3]);
		should(g.fen().substr(11, 6), "/8/1b6");
	});

	test("white promotes with capture", []() {
		Game g;
		g.restore("ppp/1P");
		should(pm(g, (9)), ",b7a8q,b7a8r,b7a8n,b7a8b,b7c8q,b7c8r,b7c8n,b7c8b");
	});

	test("black promotes with capture", []() {
		Game g;
		g.restore("//////1p/PPP");
		should(pm(g, (49)), ",b2a1q,b2a1r,b2a1n,b2a1b,b2c1q,b2c1r,b2c1n,b2c1b");
	});
}

void knightMoves() {
	test("alone", []() {
		Game g;
		g.restore("///3N");
		should(pm(g, (27)),
					",d5c7,d5e7,d5b6,d5f6,d5b4,d5f4,d5c3,d5e3");
	});

	test("limited", [](){
		Game g;
		g.restore("7n/1N//1n/7N//1N/7n");
		should(pm(g, 7), ",h8f7,h8g6");
		should(pm(g, 9), ",b7d8,b7d6,b7a5,b7c5");
		should(pm(g, 25), ",b5a7,b5c7,b5d6,b5d4,b5a3,b5c3");
		should(pm(g, 39), ",h4g6,h4f5,h4f3,h4g2");
		should(pm(g, 49), ",b2a4,b2c4,b2d3,b2d1");
		should(pm(g, 63), ",h1g3,h1f2");
	});

	test("blocked", []() {
		Game g;
		g.restore("//2P1P/1P3P/3N/1P/2P1p/");
		should(pm(g, 35), ",d4f3,d4e2");
	});
}

int main() {
	restoring();
	moving();
	pawnMoves();
	knightMoves();
}
