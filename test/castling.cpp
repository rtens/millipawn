#include "../lib/include/Game.h"
#include "base.h"

void castling() {
	test("castle white kingside", []() {
		Game g;
		g.start("//////3PPP/3PK2R w KQkq");
		should(pm(g.moves(60)), ",e1f1,e1g1");
		g.make(Move{60, 62});
		should(g.fen().substr(0, 29), "8/8/8/8/8/8/3PPP2/3P1RK1 b kq");
	});

	test("castle white queenside", []() {
		Game g;
		g.start("//////3PPP2/R3KP w KQkq");
		should(pm(g.moves(60)), ",e1d1,e1c1");
		g.make(Move{60, 58});
		should(g.fen().substr(0, 29), "8/8/8/8/8/8/3PPP2/2KR1P2 b kq");
	});

	test("castle black kingside", []() {
		Game g;
		g.start("3pk2r/3ppp2 w KQkq");
		should(pm(g.moves(4)), ",e8f8,e8g8");
		g.turn = Game::BLACK;
		g.make(Move{4, 6});
		should(g.fen().substr(0, 29), "3p1rk1/3ppp2/8/8/8/8/8/8 w KQ");
	});

	test("castle black queenside", []() {
		Game g;
		g.start("r3kp2/3ppp2 w KQkq");
		should(pm(g.moves(4)), ",e8d8,e8c8");
		g.turn = Game::BLACK;
		g.make(Move{4, 2});
		should(g.fen().substr(0, 29), "2kr1p2/3ppp2/8/8/8/8/8/8 w KQ");
	});

	test("cannot castle through pieces", []() {
		Game g;
		g.start("3pkp1r/3ppp2/////3PPP2/3PKP1R w KQkq");
		should(pm(g.moves(60)), "");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), "");
	});

	test("cannot castle when in check", []() {
		Game g;
		g.start("3pk2r/3Ppp2/////3pPP2/3PK2R w Kk");
		should(pm(g.moves(60)), ",e1d2,e1f1");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), ",e8f8,e8d7");
	});

	test("can castle when not in check", []() {
		Game g;
		g.start("r3k2r/3ppp2/4BR2/8/8/3r1q2/3PPP2/R3K2R w KQkq");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1g1,e1c1");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), ",e8d8,e8f8,e8g8,e8c8");
	});

	test("cannot castle through check", []() {
		Game g;
		g.start("r3k2r/3ppp2/1B4R1/8/8/2n3q1/3PPP2/R3K2R w KQkq");
		should(pm(g.moves(60)), ",e1f1");
		g.turn = Game::BLACK;
		should(pm(g.moves(4)), ",e8f8");
	});

	test("king prevents castling", []() {
		Game g;
		g.start("r3kp/1K1ppp b kq");
		should(pm(g.moves(4)), ",e8d8");
	});

	test("lose castling when King moves", []() {
		Game g;
		g.start("r3k2r/3ppp2/////3PPP2/R3K2R w KQkq");
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
		g.start("r3k2r/3ppp2/////3PPP2/R3K2R w KQkq");
		g.make(Move{7, 15});
		g.make(Move{63, 55});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Qq");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1c1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8c8");
	});

	test("lose queen castling when Rook moves", []() {
		Game g;
		g.start("r3k2r/3ppp2/////3PPP2/R3K2R w KQkq");
		g.make(Move{0, 8});
		g.make(Move{56, 48});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Kk");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1g1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8g8");
	});

	test("lose king castling when Rook captured", []() {
		Game g;
		g.start("r3k2r/3pppP/////3PPP2/R3K2R w KQkq");
		g.make(Move{14, 7});
		g.make(Move{54, 63});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Qq");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1c1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8c8");
	});

	test("lose queen castling when Rook captured", []() {
		Game g;
		g.start("r3k2r/1P1ppp2/////1p1PPP2/R3K2R w KQkq");
		g.make(Move{9, 0});
		g.make(Move{49, 56});
		should(g.fen().substr(g.fen().find_first_of(' ') + 1, 4), "w Kk");
		should(pm(g.moves(60)), ",e1d1,e1f1,e1g1");
		should(pm(g.moves(4)), ",e8d8,e8f8,e8g8");
	});

	test("only castle King side with rights", []() {
		Game g;
		g.start("4r2b///////4R2B");
		g.make(Move{60, 62});
		g.make(Move{4, 6});
		should(g.fen().substr(0, 20), "6rb/8/8/8/8/8/8/6RB ");
	});

	test("only castle Queen side with rights", []() {
		Game g;
		g.start("b3r3///////B3R3");
		g.make(Move{60, 58});
		g.make(Move{4, 2});
		should(g.fen().substr(0, 22), "b1r5/8/8/8/8/8/8/B1R5 ");
	});
}
