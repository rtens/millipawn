using namespace std;
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

#include "../lib/include/Game.h"

void should(bool fact, string message)
{
  if (!fact)
    throw message;
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

void restoring()
{
  test("overwrite pieces", []()
       {
    Game g;
    g.restore("8/8/8/8/8/8/8/P7 w - - 0 1");
    g.restore("8/8/8/8/8/8/P7/8 w - - 0 1");
    should(g.fen() == "8/8/8/8/8/8/P7/8 w - - 0 1", "Not overwritten: " + g.fen()); });
}

void moving()
{
  test("start with empty board", []()
       {
    Game g;
    should(g.turn == Game::WHITE, "First turn not white");
    should(g.fen() == "8/8/8/8/8/8/8/8 w - - 0 1", "Not empty: " + g.fen()); });

  test("blacks turn", []()
       {
    Game g;
    g.restore("8/8/8/8/8/8/8/8 b - - 0 1");
    should(g.turn == Game::BLACK, "First turn not black");
    should(g.fen() == "8/8/8/8/8/8/8/8 b - - 0 1", "Not blacks turn: " + g.fen()); });

  test("simple move", []()
       {
    Game g;
    g.restore("8/8/8/8/8/8/8/7P w - - 0 1");
    g.make(Move{63, 63 - 16});
    should(g.turn == Game::BLACK, "Second turn not black");
    should(g.fen() == "8/8/8/8/8/7P/8/8 b - - 0 1", "Pawn not in 3rd row: " + g.fen()); });
}

string printMoves(vector<Move> moves)
{
  return accumulate(moves.begin(), moves.end(), string(),
                    [](const string &s, Move m)
                    { return s + "," + Game::print(m); });
}

void pawnMoves()
{
  test("start moves", []()
       {
    Game g;
    g.restore("8/p7/8/8/8/8/P7/8 w - - 0 1");
    auto moves = printMoves(g.moves(48));
    should(moves == ",a2a3,a2a4", "Moves white: " + moves);
    moves = printMoves(g.moves(8));
    should(moves == ",a7a6,a7a5", "Moves black: " + moves); });

  test("normal move", []()
       {
    Game g;
    g.restore("8/8/p7/8/8/P7/8/8 w - - 0 1");
    auto moves = printMoves(g.moves(40));
    should(moves == ",a3a4", "Moves: " + moves);
    moves = printMoves(g.moves(16));
    should(moves == ",a6a5", "Moves: " + moves); });

  test("blocked", []()
       {
    Game g;
    g.restore("8/8/8/8/PP6/P7/PP6/8");

    auto moves = printMoves(g.moves(48));
    should(moves == "", "Moves: " + moves);

    moves = printMoves(g.moves(40));
    should(moves == "", "Moves: " + moves);

    moves = printMoves(g.moves(49));
    should(moves == ",b2b3", "Moves: " + moves); });

  test("capture", []() {

  });
}

int main()
{
  restoring();
  moving();
  pawnMoves();
}