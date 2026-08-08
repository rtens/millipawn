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

string pm(vector<Move> moves) {
  return accumulate(
      moves.begin(), moves.end(), string(),
      [](const string& s, Move m) { return s + "," + Game::print(m); });
}

void pawnMoves() {
  test("start moves", []() {
    Game g;
    g.restore("/p/////P w - - 0 1");

    should(pm(g.moves(48)), ",a2a3,a2a4");
    should(pm(g.moves(8)), ",a7a6,a7a5");
  });

  test("normal move", []() {
    Game g;
    g.restore("//p///P// w - - 0 1");

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
}

int main() {
  restoring();
  moving();
  pawnMoves();
}
