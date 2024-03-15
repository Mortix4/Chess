#pragma once


#include "Piece.h"

class King : public Piece
{

public:
	King(Color c, int x, int y, PieceType type);
	~King();

	vector<Square*> getPossibleMoves() override;
};