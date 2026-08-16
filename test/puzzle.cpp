// #include "../lib/include/Puzzle.h"

// #include "../lib/include/Game.h"
// #include "base.h"

// void puzzle() {
// 	test("solved puzzle", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("", {});
// 		should(g.fen(), Game::STARTPOS, "start");
// 		should(p.propose(Move{62, 62 - 17}), Puzzle::SOLVED);
// 		should(g.fen(), Game::STARTPOS, "end");
// 	});

// 	test("solve puzzle", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("e4 e5", {"g1f3"});
// 		should(p.propose(Move{62, 62 - 17}), Puzzle::SOLVED);
// 		should(Game::print(p.last), "g1f3");
// 	});

// 	test("right move", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("e4 e5", {"g1f3", "b8c6", "f1c4"});
// 		should(p.propose(Move{62, 62 - 17}), Puzzle::RIGHT);
// 		should(Game::print(p.last), "b8c6");
// 		should(g.fen(),
// 					 "r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0
// 1"); 		should(p.propose(Move{61, 34}), Puzzle::SOLVED);
// 		should(Game::print(p.last), "f1c4");
// 	});

// 	test("wrong move", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("e4 e5", {"g1f3"});
// 		should(p.propose(Move{61, 61 - 9}), Puzzle::WRONG);
// 		should(g.fen(),
// 					 "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPPBPPP/RNBQK1NR b KQkq - 0 1");
// 	});

// 	test("correct wrong move", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("e4 e5", {"g1f3"});
// 		should(p.propose(Move{61, 61 - 9}), Puzzle::WRONG);
// 		p.undo();
// 		should(p.last.from, -1);
// 		should(p.last.to, -1);
// 		should(g.fen(),
// 					 "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 1");
// 		should(p.propose(Move{62, 62 - 17}), Puzzle::SOLVED, "solved");
// 	});

// 	test("nothing to undo", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("e4 e5", {"g1f3"});
// 		p.undo();
// 		should(g.fen(),
// 					 "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 1");
// 		should(p.propose(Move{62, 62 - 17}), Puzzle::SOLVED, "solved");
// 	});

// 	test("provide next move", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("e4 e5", {"g1f3"});
// 		should(Game::print(p.hint()), "g1f3");
// 	});

// 	test("alternative checkmate", []() {
// 		Game g;
// 		Puzzle p(&g);
// 		p.start("e4 a6 Qh5 b6 Bc4 h6", {"h5f7"});
// 		should(p.propose(Move{Game::toSquare("c4"), Game::toSquare("f7")}),
// 					 Puzzle::SOLVED);
// 	});
// }
