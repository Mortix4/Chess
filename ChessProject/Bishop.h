#pragma once


#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(Color c, int x, int y, PieceType type);
	~Bishop();
	vector<Square*> getPossibleMoves() override;
};