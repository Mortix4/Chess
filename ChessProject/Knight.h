#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(Color c, int x, int y, PieceType type);
	~Knight();

	vector<Square*> getPossibleMoves() override;
};