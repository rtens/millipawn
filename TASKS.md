# Project Tasks

## Current

- Fix move generation
  - Bishop takes en passant


## Planned: Puzzle

API: https://lichess.org/api#tag/puzzles

- Start puzzle
	- load PGN
	- parse solution

- Reject wrong move

- Accept right move

- Solve puzzle

- UI
	- download puzzles
		- request API
		- read response
		- store puzzles
	- next puzzle
		- read next puzzle
		- start puzzle
		- save current index
	- make move
	- show rejection
	- show acceptance
	- respond to correct move
	- show solved


## Ideas: AI

- Random response

- Best evaluation response

- Deep search

- Alpha-beta pruning

- Order moves

- Captures extension

- Piece square tables

- Openings

- Iterative deepening

- Transposition tables

- End game heuristics

- Different strengths


## Ideas

- Export PGN of game


## Completed

- Test position trees

- Game over
	- Checkmate
	- Stalemate

- Prevent illegal moves

- Undo move
	- simple move
	- capture
	- promotion
	- en passant
	- castling

- King prevents castling

- En passant

- Castle
	- move rooks
	- lose rights
	- print rights
	- parse rights
	- consider checks

- Move King

- Move Queen

- Move Rook

- Move Bishop

- Move Knight

- Promote Pawn
	- with move
	- with capture

- Pawn capture

- Move Pawn

- Read and print FEN

- Only pieces
