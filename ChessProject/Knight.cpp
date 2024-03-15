#include "Knight.h"

Knight::Knight(Color c, int x, int y, PieceType type) : Piece(c, x,  y, type)
{

}

Knight::~Knight()
{

}

vector<Square*> Knight::getPossibleMoves()
{
    int x = _x, y = _y;
    vector<Square*> possibleSquars(0);
	
	//adding all the possible moves out of the 8 direction an knight can move to
	if (isInBoard((x + 1), (y + 2)))
	{
		possibleSquars.push_back(new Square((x + 1), (y + 2)));
	}
	if (isInBoard((x + 2), (y + 1)))
	{
		possibleSquars.push_back(new Square((x + 2), (y + 1)));
	}
	if (isInBoard((x + 2), (y - 1)))
	{
		possibleSquars.push_back(new Square((x + 2), (y - 1)));
	}

	if (isInBoard((x + 1), (y - 2)))
	{
		possibleSquars.push_back(new Square((x + 1), (y - 2)));
	}

	if (isInBoard((x - 1), (y - 2)))
	{
		possibleSquars.push_back(new  Square((x - 1), (y - 2)));
	}

	if (isInBoard((x - 2), (y - 1)))
	{
		possibleSquars.push_back(new Square((x - 2), (y - 1)));
	}

	if (isInBoard((x - 2), (y + 1)))
	{
		possibleSquars.push_back(new Square((x - 2), (y + 1)));
	}

	if (isInBoard((x - 1), (y + 2)))
	{
		possibleSquars.push_back(new  Square((x - 1), (y + 2)));
	}

    return possibleSquars;
}
