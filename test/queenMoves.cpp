// #include "../lib/include/Game.h"
// #include "base.h"

// void queenMoves() {
// 	test("free", []() {
// 		Game g;
// 		g.start("///3Q");
// 		should(pm(g.moves(27)),
// 					 ",d5d6,d5d7,d5d8"
// 					 ",d5c5,d5b5,d5a5"
// 					 ",d5e5,d5f5,d5g5,d5h5"
// 					 ",d5d4,d5d3,d5d2,d5d1"
// 					 ",d5c6,d5b7,d5a8"
// 					 ",d5e6,d5f7,d5g8"
// 					 ",d5c4,d5b3,d5a2"
// 					 ",d5e4,d5f3,d5g2,d5h1");
// 	});

// 	test("blocked", []() {
// 		Game g;
// 		g.start("/3P/2P1P/1P1Q2P/3P/5P/P7/");
// 		should(pm(g.moves(27)),
// 					 ",d5d6"
// 					 ",d5c5"
// 					 ",d5e5,d5f5"
// 					 ",d5c4,d5b3"
// 					 ",d5e4");
// 	});

// 	test("capture", []() {
// 		Game g;
// 		g.start("/3P/2P1P/1P1q2P/3P/5P/P7/");
// 		should(pm(g.moves(27)),
// 					 ",d5d6,d5d7"
// 					 ",d5c5,d5b5"
// 					 ",d5e5,d5f5,d5g5"
// 					 ",d5d4"
// 					 ",d5c6"
// 					 ",d5e6"
// 					 ",d5c4,d5b3,d5a2"
// 					 ",d5e4,d5f3");
// 	});
// }
