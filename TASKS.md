# Project Tasks

## Current


## Planned: Puzzle

- Seperate proposal and response


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

- Refactor into Board, Piece, Move, Game, Parser, Printer (in namespace Chess)

- Export PGN of game


## Completed

- Fix move generation
	- Initial Position
	- Bishop does not take en passant
	- Rook cannot be taken en passant
	- Pawns attack diagonally

- Any checkmate solves a puzzle

- Provide next step

- Play a puzzle
	- start puzzle
	- solve puzzle
	- reject wrong move
	- accept right move
	- correct wrong move

- Parse PGN

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
