#pragma once


#include "Piece.h"

class Pawn : public Piece
{
private:
	bool _isFirstMove; // Used to know if t he piece can move 2 squares

public:
	Pawn(Color c, int x, int y, PieceType type);
	~Pawn();

	bool getFirstMove();
	void setFirstMove(bool fmove);

	vector<Square*> getPossibleMoves() override;
};