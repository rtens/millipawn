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
		cout << endl << "X " << name << ": " << e << endl;
	}
}

void restoring() {
	test("empty board", []() {
		Game g;
		should(g.turn, Game::WHITE);
		should(g.fen().substr(0, 15), "8/8/8/8/8/8/8/8");
	});

	test("starting position", []() {
		Game g;
		g.restore(Game::STARTPOS);
		should(g.turn, Game::WHITE);
		should(g.fen(), Game::STARTPOS);
	});

	test("mixed position", []() {
		Game g;
		string mixed = "3r2B1/p3pp2/5Q2/kN3RpP/3P2P1/6P1/2PP2PP/7K";
		g.restore(mixed);
		should(g.fen().substr(0, mixed.length()), mixed);
	});

	test("blacks turn", []() {
		Game g;
		g.restore("/////// b");
		should(g.fen().substr(16, 1), "b");
	});

	test("overwrite pieces", []() {
		Game g;
		g.restore("P");
		g.restore("8/P");
		should(g.fen().substr(0, 16), "8/P7/8/8/8/8/8/8");
	});

	test("castling", []() {
		Game g;
		g.restore("/ w KQkq");
		should(g.fen().substr(17, 6), " KQkq ");
		g.restore("/ w Kq");
		should(g.fen().substr(17, 4), " Kq ");
		g.restore("/");
		should(g.fen().substr(17, 3), " - ");
		g.restore("/ w -");
		should(g.fen().substr(17, 3), " - ");
	});

	test("en passant", []() {
		Game g;
		g.restore("/ w - g3");
		should(g.fen().substr(19, 4), " g3 ");
		g.restore("/");
		should(g.fen().substr(19, 3), " - ");
		g.restore("/ w - -");
		should(g.fen().substr(19, 3), " - ");
	});
}

void moving() {
	test("blacks turn", []() {
		Game g;
		g.restore("/ b");
		should(g.turn, Game::BLACK);
		should(g.fen().substr(16, 1), "b");
	});

	test("simple move", []() {
		Game g;
		g.restore("/P w");
		g.make(Move{8, 20});
		should(g.turn, Game::BLACK);
		should(g.fen().substr(0, 19), "8/8/4P3/8/8/8/8/8 b");
	});
}

string pm(vector<Move> moves) {
	return accumulate(
			moves.begin(), moves.end(), string(),
			[](const string& s, Move m) { return s + "," + Game::print(m); });
}

void pawnMoves() {
	test("start moves", []() {
		Game g;
		g.restore("/p/////P");

		should(pm(g.moves(48)), ",a2a3,a2a4");
		should(pm(g.moves(8)), ",a7a6,a7a5");
	});

	test("normal move", []() {
		Game g;
		g.restore("//p///P//");

		should(pm(g.moves(40)), ",a3a4");
		should(pm(g.moves(16)), ",a6a5");
	});

	test("blocked", []() {
		Game g;
		g.restore("////PP/P/PP");

		should(pm(g.moves(48)), "");
		should(pm(g.moves(40)), "");
		should(pm(g.moves(49)), ",b2b3");
	});

	test("capture", []() {
		Game g;
		g.restore("/2ppp/3P//3p/2PPP");

		should(pm(g.moves(19)), ",d6c7,d6e7");
		should(pm(g.moves(35)), ",d4c3,d4e3");
	});

	test("capture on left edge", []() {
		Game g;
		g.restore("7p/pp/P//p6P/PP");
		should(pm(g.moves(16)), ",a6b7");
		should(pm(g.moves(32)), ",a4b3");
	});

	test("capture on right edge", []() {
		Game g;
		g.restore("/6pp/p6P//7p/6PP/P");
		should(pm(g.moves(23)), ",h6g7");
		should(pm(g.moves(39)), ",h4g3");
	});

	test("white promotes with move", []() {
		Game g;
		g.restore("8/1P");
		should(pm(g.moves(9)), ",b7b8q,b7b8r,b7b8n,b7b8b");

		auto moves = g.moves(9);

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
		should(pm(g.moves(49)), ",b2b1q,b2b1r,b2b1n,b2b1b");

		auto moves = g.moves(49);

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
		should(pm(g.moves(9)), ",b7a8q,b7a8r,b7a8n,b7a8b,b7c8q,b7c8r,b7c8n,b7c8b");
	});

	test("black promotes with capture", []() {
		Game g;
		g.restore("//////1p/PPP");
		should(pm(g.moves(49)), ",b2a1q,b2a1r,b2a1n,b2a1b,b2c1q,b2c1r,b2c1n,b2c1b");
	});
}

void knightMoves() {
	test("alone", []() {
		Game g;
		g.restore("///3N");
		should(pm(g.moves(27)), ",d5c7,d5e7,d5b6,d5f6,d5b4,d5f4,d5c3,d5e3");
	});

	test("limited", []() {
		Game g;
		g.restore("7n/1N//1n/7N//1N/7n");
		should(pm(g.moves(7)), ",h8f7,h8g6");
		should(pm(g.moves(9)), ",b7d8,b7d6,b7a5,b7c5");
		should(pm(g.moves(25)), ",b5a7,b5c7,b5d6,b5d4,b5a3,b5c3");
		should(pm(g.moves(39)), ",h4g6,h4f5,h4f3,h4g2");
		should(pm(g.moves(49)), ",b2a4,b2c4,b2d3,b2d1");
		should(pm(g.moves(63)), ",h1g3,h1f2");
	});

	test("blocked", []() {
		Game g;
		g.restore("//2P1P/1P3P/3N/1P/2P1P/");
		should(pm(g.moves(35)), ",d4f3");
	});

	test("capture", []() {
		Game g;
		g.restore("//2p1P/1P3P/3N/1P3P/2P1p/");
		should(pm(g.moves(35)), ",d4c6,d4e2");
	});
}

void bishopMoves() {
	test("free", []() {
		Game g;
		g.restore("///3B");
		should(pm(g.moves(27)),
					 ",d5c6,d5b7,d5a8"
					 ",d5e6,d5f7,d5g8"
					 ",d5c4,d5b3,d5a2"
					 ",d5e4,d5f3,d5g2,d5h1");
	});

	test("blocked", []() {
		Game g;
		g.restore("P//4P/3B//1P3P//");
		should(pm(g.moves(27)), ",d5c6,d5b7,d5c4,d5e4");
	});

	test("capture", []() {
		Game g;
		g.restore("p//4p/3B//1p3p//");
		should(pm(g.moves(27)), ",d5c6,d5b7,d5a8,d5e6,d5c4,d5b3,d5e4,d5f3");
	});
}

void rookMoves() {
	test("free", []() {
		Game g;
		g.restore("///3R");
		should(pm(g.moves(27)),
					 ",d5d6,d5d7,d5d8"
					 ",d5c5,d5b5,d5a5"
					 ",d5e5,d5f5,d5g5,d5h5"
					 ",d5d4,d5d3,d5d2,d5d1");
	});

	test("blocked", []() {
		Game g;
		g.restore("/3P//1P1R2P/3P");
		should(pm(g.moves(27)),
					 ",d5d6"
					 ",d5c5"
					 ",d5e5,d5f5");
	});

	test("capture", []() {
		Game g;
		g.restore("/3p//1p1R2p/3p");
		should(pm(g.moves(27)),
					 ",d5d6,d5d7"
					 ",d5c5,d5b5"
					 ",d5e5,d5f5,d5g5"
					 ",d5d4");
	});
}

void queenMoves() {
	test("free", []() {
		Game g;
		g.restore("///3Q");
		should(pm(g.moves(27)),
					 ",d5d6,d5d7,d5d8"
					 ",d5c5,d5b5,d5a5"
					 ",d5e5,d5f5,d5g5,d5h5"
					 ",d5d4,d5d3,d5d2,d5d1"
					 ",d5c6,d5b7,d5a8"
					 ",d5e6,d5f7,d5g8"
					 ",d5c4,d5b3,d5a2"
					 ",d5e4,d5f3,d5g2,d5h1");
	});

	test("blocked", []() {
		Game g;
		g.restore("/3P/2P1P/1P1Q2P/3P/5P/P7/");
		should(pm(g.moves(27)),
					 ",d5d6"
					 ",d5c5"
					 ",d5e5,d5f5"
					 ",d5c4,d5b3"
					 ",d5e4");
	});

	test("capture", []() {
		Game g;
		g.restore("/3P/2P1P/1P1q2P/3P/5P/P7/");
		should(pm(g.moves(27)),
					 ",d5d6,d5d7"
					 ",d5c5,d5b5"
					 ",d5e5,d5f5,d5g5"
					 ",d5d4"
					 ",d5c6"
					 ",d5e6"
					 ",d5c4,d5b3,d5a2"
					 ",d5e4,d5f3");
	});
}

void kingMoves() {
	test("free", []() {
		Game g;
		g.restore("///3K");
		should(pm(g.moves(27)), ",d5c6,d5d6,d5e6,d5c5,d5e5,d5c4,d5d4,d5e4");
	});

	test("blocked", []() {
		Game g;
		g.restore("//2PP/3KP/2PP");
		should(pm(g.moves(27)), ",d5e6,d5c5,d5e4");
	});

	test("capture", []() {
		Game g;
		g.restore("//2pP/3Kp/2PP");
		should(pm(g.moves(27)), ",d5c6,d5e6,d5c5,d5e5,d5e4");
	});
}

void castling() {
	test("castle white kingside", []() {
		Game g;
		g.restore("//////3PPP/3PK2R w KQkq");
		should(pm(g.moves(60)), ",e1f1,e1g1");
		g.make(Move{60, 62});
		should(g.fen().substr(0, 29), "8/8/8/8/8/8/3PPP2/3P1RK1 b kq");
	});
	test("castle white queenside", []() {
		Game g;
		g.restore("//////3PPP2/R3KP w KQkq");
		should(pm(g.moves(60)), ",e1d1,e1c1");
		g.make(Move{60, 58});
		should(g.fen().substr(0, 29), "8/8/8/8/8/8/3PPP2/2KR1P2 b kq");
	});
	test("castle black kingside", []() {
		Game g;
		g.restore("3pk2r/3ppp2 w KQkq");
		should(pm(g.moves(4)), ",e8f8,e8g8");
		g.turn = Game::BLACK;
		g.make(Move{4, 6});
		should(g.fen().substr(0, 29), "3p1rk1/3ppp2/8/8/8/8/8/8 w KQ");
	});
	test("castle black queenside", []() {
		Game g;
		g.restore("r3kp2/3ppp2 w KQkq");
		should(pm(g.moves(4)), ",e8d8,e8c8");
		g.turn = Game::BLACK;
		g.make(Move{4, 2});
		should(g.fen().substr(0, 29), "2kr1p2/3ppp2/8/8/8/8/8/8 w KQ");
	});

	test("cannot castle through pieces", []() {
		Game g;
		g.restore("3pkp1r/3ppp2/////3PPP2/3PKP1R w KQkq");
		should(pm(g.moves(60)), "");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), "");
	});
	test("cannot castle when in check", []() {
		Game g;
		g.restore("3pk2r/3Ppp2/////3pPP2/3PK2R w Kk");
		should(pm(g.moves(60)), ",e1d2,e1f1");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), ",e8f8,e8d7");
	});
	test("can castle when not in check", []() {
		Game g;
		g.restore("r3k2r/3ppp2/4BR2/8/8/3r1q2/3PPP2/R3K2R w KQkq");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1g1,e1c1");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), ",e8d8,e8f8,e8g8,e8c8");
	});
	test("cannot castle through check", []() {
		Game g;
		g.restore("r3k2r/3ppp2/1B4R1/8/8/2n3q1/3PPP2/R3K2R w KQkq");
		should(pm(g.moves(60)), ",e1f1");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), ",e8f8");
	});
	test("king prevents castling", []() {
		Game g;
		g.restore("r3kp/1K1ppp b kq");
		should(pm(g.moves(4)), ",e8d8");
	});

	test("lose castling when King moves", []() {
		Game g;
		g.restore("r3k2r/3ppp2/////3PPP2/R3K2R w KQkq");
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 6), "w KQkq");
		g.make(Move{4, 3});
		g.make(Move{3, 4});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w KQ");
		g.make(Move{60, 61});
		g.make(Move{61, 60});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 3), "w -");
		should(pm(g.moves(60)), ",e1d1,e1f1");
		should(pm(g.moves(4)), ",e8d8,e8f8");
	});
	test("lose king castling when Rook moves", []() {
		Game g;
		g.restore("r3k2r/3ppp2/////3PPP2/R3K2R w KQkq");
		g.make(Move{7, 15});
		g.make(Move{63, 55});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Qq");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1c1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8c8");
	});
	test("lose queen castling when Rook moves", []() {
		Game g;
		g.restore("r3k2r/3ppp2/////3PPP2/R3K2R w KQkq");
		g.make(Move{0, 8});
		g.make(Move{56, 48});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Kk");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1g1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8g8");
	});
	test("lose king castling when Rook captured", []() {
		Game g;
		g.restore("r3k2r/3pppP/////3PPP2/R3K2R w KQkq");
		g.make(Move{14, 7});
		g.make(Move{54, 63});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Qq");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1c1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8c8");
	});
	test("lose queen castling when Rook captured", []() {
		Game g;
		g.restore("r3k2r/1P1ppp2/////1p1PPP2/R3K2R w KQkq");
		g.make(Move{9, 0});
		g.make(Move{49, 56});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Kk");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1g1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8g8");
	});

	test("only castle King side with rights", []() {
		Game g;
		g.restore("4r2b///////4R2B");
		g.make(Move{60, 62});
		g.make(Move{4, 6});
		should(g.fen().substr(0, 20), "6rb/8/8/8/8/8/8/6RB ");
	});
	test("only castle Queen side with rights", []() {
		Game g;
		g.restore("b3r3///////B3R3");
		g.make(Move{60, 58});
		g.make(Move{4, 2});
		should(g.fen().substr(0, 22), "b1r5/8/8/8/8/8/8/B1R5 ");
	});
}

void enPassant() {
	test("white takes", []() {
		Game g;
		g.restore("/3p//2P b");
		g.make(Move{11, 27});
		should(g.fen().substr(g.fen().find_first_of(' '), 8), " w - d6 ");
		should(pm(g.moves(26)), ",c5c6,c5d6");
		g.make(Move{26, 19});
		should(g.fen().substr(0, 24), "8/8/3P4/8/8/8/8/8 b - - ");
	});
	test("black takes", []() {
		Game g;
		g.restore("////4p//3P w");
		g.make(Move{51, 35});
		should(g.fen().substr(g.fen().find_first_of(' '), 8), " b - d3 ");
		should(pm(g.moves(36)), ",e4e3,e4d3");
		g.make(Move{36, 43});
		should(g.fen().substr(0, 24), "8/8/8/8/8/3p4/8/8 w - - ");
	});
}

void undo() {
	test("nothing to undo", []() {
		Game g;
		g.restore("//3R/PP3K");
		g.undo();
		should(g.fen().substr(0, 23), "8/8/3R4/PP3K2/8/8/8/8 w");
	});

	test("simple move", []() {
		Game g;
		g.restore("//3R/PP3K");
		g.make(Move{19, 3});
		should(g.fen().substr(0, 23), "3R4/8/8/PP3K2/8/8/8/8 b");
		g.undo();
		should(g.fen().substr(0, 23), "8/8/3R4/PP3K2/8/8/8/8 w");
	});

	test("capture", []() {
		Game g;
		g.restore("3b//3R/PP3K");
		g.make(Move{19, 3});
		should(g.fen().substr(0, 23), "3R4/8/8/PP3K2/8/8/8/8 b");
		g.undo();
		should(g.fen().substr(0, 25), "3b4/8/3R4/PP3K2/8/8/8/8 w");
	});

	test("promotion", []() {
		Game g;
		g.restore("/3P");
		g.make(Move{11, 3, Game::QUEEN});
		g.undo();
		should(g.fen().substr(0, 5), "8/3P4");
	});

	test("en passant white", []() {
		Game g;
		g.restore("///2Pp w - d6");
		g.make(Move{26, 19});
		g.undo();
		should(g.fen().substr(0, 26), "8/8/8/2Pp4/8/8/8/8 w - d6 ");
	});

	test("en passant black", []() {
		Game g;
		g.restore("////2Pp b - c3");
		g.make(Move{35, 42});
		g.undo();
		should(g.fen().substr(0, 26), "8/8/8/8/2Pp4/8/8/8 b - c3 ");
	});

	test("restore en passant", []() {
		Game g;
		g.restore("r////2Pp b - c3");
		g.make(Move{0, 1});
		g.undo();
		should(g.fen().substr(0, 27), "r7/8/8/8/2Pp4/8/8/8 b - c3 ");
	});

	test("castling", []() {
		Game g;
		g.restore("r3k2r///////R3K2R w KQkq");

		g.make(Move{4, 2});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{4, 6});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{60, 58});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{60, 62});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{0, 8});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{56, 48});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");

		g.make(Move{4, 12});
		g.undo();
		should(g.fen().substr(0, 30), "r3k2r/8/8/8/8/8/8/R3K2R w KQkq");
	});
}

void illegalMoves() {
	test("self-check", []() {
		Game g;
		g.restore("///3r4///4PP2/4K3");
		should(pm(g.moves(60)), ",e1f1");
	});

	test("pinned piece", []() {
		Game g;
		g.restore("///4r///4R/4K");
		should(pm(g.moves(52)), ",e2e3,e2e4,e2e5");
	});
}

int main() {
	restoring();
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

	cout << endl;
}
