#pragma once

#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"

class Queen : public Piece
{
public:
	Queen(Color c, int x, int y, PieceType type);
	~Queen();

	vector<Square*> getPossibleMoves() override;
};