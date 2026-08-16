// #include "../lib/include/Game.h"
// #include "base.h"

// void knightMoves() {
// 	test("alone", []() {
// 		Game g;
// 		g.start("///3N");
// 		should(pm(g.moves(27)), ",d5c7,d5e7,d5b6,d5f6,d5b4,d5f4,d5c3,d5e3");
// 	});

// 	test("limited", []() {
// 		Game g;
// 		g.start("7n/1N//1n/7N//1N/7n");
// 		should(pm(g.moves(7)), ",h8f7,h8g6");
// 		should(pm(g.moves(9)), ",b7d8,b7d6,b7a5,b7c5");
// 		should(pm(g.moves(25)), ",b5a7,b5c7,b5d6,b5d4,b5a3,b5c3");
// 		should(pm(g.moves(39)), ",h4g6,h4f5,h4f3,h4g2");
// 		should(pm(g.moves(49)), ",b2a4,b2c4,b2d3,b2d1");
// 		should(pm(g.moves(63)), ",h1g3,h1f2");
// 	});

// 	test("blocked", []() {
// 		Game g;
// 		g.start("//2P1P/1P3P/3N/1P/2P1P/");
// 		should(pm(g.moves(35)), ",d4f3");
// 	});

// 	test("capture", []() {
// 		Game g;
// 		g.start("//2p1P/1P3P/3N/1P3P/2P1p/");
// 		should(pm(g.moves(35)), ",d4c6,d4e2");
// 	});
// }
