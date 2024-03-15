
#include "Pawn.h"

Pawn::Pawn(Color c, int x, int y, PieceType type) : Piece(c, x, y, type)
{
	_isFirstMove = true;
}

Pawn::~Pawn()
{

}

bool Pawn::getFirstMove()
{
	return _isFirstMove;
}
void Pawn::setFirstMove(bool fmove)
{
	_isFirstMove = fmove;
}


vector<Square*> Pawn::getPossibleMoves()
{
	int x = _x, y = _y;

	vector<Square*> possibleSquars(0);

	//down left corner is 0, 0
	if (_color == WHITE) // white moves up the board
	{
		//adding moving squares
		possibleSquars.push_back(new Square(x, (y + 1)));
		if (_isFirstMove) //checking if the Pawn can travel 2 squares (Only at the first time it moves)
		{
			possibleSquars.push_back(new Square(x, (y + 2)));
			_isFirstMove = false;
		}

		//adding eating squares
		possibleSquars.push_back(new Square((x + 1), (y + 1)));

		possibleSquars.push_back(new Square((x - 1), (y + 1)));
	}
	else // color == BLACK // BLACK moves down the board
	{
		//adding moving squares
		possibleSquars.push_back(new Square(x, (y - 1)));

		if (_isFirstMove)
		{
			
			possibleSquars.push_back(new Square(x, (y - 2)));
			_isFirstMove = false;
		}

		//adding eating squares
		possibleSquars.push_back(new Square((x + 1), (y - 1)));


		possibleSquars.push_back(new Square((x - 1), (y - 1)));
	}

	return possibleSquars;
}