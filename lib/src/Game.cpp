using namespace std;
#include "../include/Game.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Game::make(Move move)
{
  turn ^= 24;
  pieces[move.to] = pieces[move.from];
  pieces[move.from] = EMPTY;
}

vector<Move> Game::moves(int square)
{
  vector<Move> moves;

  switch (pieces[square] & TYPE)
  {
  case PAWN:
    int dir = 1;
    int startRow = 1;
    if (pieces[square] & WHITE)
    {
      dir = -1;
      startRow = 6;
    }

    int one_step = square + (8 * dir);
    int two_steps = square + (16 * dir);
    if (pieces[one_step] == EMPTY)
    {
      moves.push_back(Move{square, one_step});

      if (square / 8 == startRow && pieces[two_steps] == EMPTY)
      {
        moves.push_back(Move{square, two_steps});
      }
    }
    break;
  }

  return moves;
}

string Game::print(Move move)
{
  stringstream ss;

  ss << char((move.from % 8) + 'a') << 8 - (move.from / 8);
  ss << char((move.to % 8) + 'a') << 8 - (move.to / 8);

  return ss.str();
}

string Game::fen()
{
  stringstream ss;

  int empties = 0;
  for (int i = 0; i < 64; i++)
  {
    if (i > 0 && i % 8 == 0)
    {
      if (empties)
      {
        ss << empties;
        empties = 0;
      }
      ss << "/";
    }

    if (pieces[i] == EMPTY)
    {
      empties++;
      continue;
    }
    else if (empties)
    {
      ss << to_string(empties);
      empties = 0;
    }

    switch (pieces[i])
    {
    case WHITE | PAWN:
      ss << "P";
      break;
    case BLACK | PAWN:
      ss << "p";
      break;
    }
  }

  if (empties)
  {
    ss << empties;
    empties = 0;
  }

  ss << " ";

  if (turn == WHITE)
  {
    ss << "w";
  }
  else
  {
    ss << "b";
  }

  ss << " - - 0 1";
  return ss.str();
}

void Game::restore(string fen)
{
  const int p_pieces = 0;
  const int p_turn = 1;
  const int p_castle = 2;
  const int p_passant = 3;
  int part = p_pieces;

  int row = 0;
  int col = 0;

  for (int i = 0; i < fen.length(); i++)
  {
    if (fen[i] == ' ')
    {
      part++;
      continue;
    }

    switch (part)
    {
    case p_pieces:
      switch (fen[i])
      {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        for (; col < fen[i] - '0'; col++)
        {
          pieces[row * 8 + col] = EMPTY;
        }
        break;
      case 'P':
        pieces[row * 8 + col++] = WHITE | PAWN;
        break;
      case 'p':
        pieces[row * 8 + col++] = BLACK | PAWN;
        break;
      case '/':
        row++;
        col = 0;
        break;
      }
      break;

    case p_turn:
      switch (fen[i])
      {
      case 'w':
        turn = WHITE;
        break;
      case 'b':
        turn = BLACK;
        break;
      }
    }
  }
}