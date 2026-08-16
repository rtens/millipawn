// #include "../lib/include/Game.h"
// #include "base.h"

// void illegalMoves() {
// 	test("self-check", []() {
// 		Game g;
// 		g.start("///3r4///4PP2/4K3");
// 		should(pm(g.moves(60)), ",e1f1");
// 	});

// 	test("pinned piece", []() {
// 		Game g;
// 		g.start("///4r///4R/4K");
// 		should(pm(g.moves(52)), ",e2e3,e2e4,e2e5");
// 	});

// 	test("pinned checker", []() {
// 		Game g;
// 		g.start("8/8/3k2bR/8/8/P2K4/8/8 w");
// 		should(pm(g.moves(43)), ",d3c4,d3d4,d3c3,d3e3,d3d2,d3e2");
// 		should(pm(g.moves(40)), "");
// 	});
// }
