#include "Rook.h"

Rook::Rook(Color c, int x, int y, PieceType type) : Piece(c, x, y, type)
{

}

Rook::~Rook()
{

}

vector<Square*> Rook::getPossibleMoves()
{
	int pCol = getX(), pRow = getY();
	int row = 0, col = 0;

	vector<Square*> possibleSquars(0);


	for (row = 0; row < BOARD_SIDE_SIZE; row++)//gettes all the squares in the col of the rook
	{
		if (row != pRow) {
			possibleSquars.push_back(new Square(pCol, row, nullptr));
		}
	}

	for (col = 0; col < BOARD_SIDE_SIZE; col++)//gettes all the squares in the row of the rook
	{
		if (col != pCol) {
			possibleSquars.push_back(new  Square(col, pRow, nullptr));
		}
	}
	return possibleSquars;
}
