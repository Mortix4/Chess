#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(Color c, int x, int y, PieceType type);
	~Rook();

	vector<Square*> getPossibleMoves() override;
};