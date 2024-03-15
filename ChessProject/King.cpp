#include "King.h" 

King::King(Color c, int x, int y, PieceType type) : Piece(c, x, y, type)
{

}

King::~King()
{

}

vector<Square*> King::getPossibleMoves()
{
	int x = _x, y = _y;
	int i = 0;
	vector<Square*> possibleSquars(0);
	int xMoves[BOARD_SIDE_SIZE] = {0, 1, 1, 1, 0,-1,-1,-1};
	int yMoves[BOARD_SIDE_SIZE] = {1, 1, 0,-1,-1,-1, 0, 1};
	Square tmp = Square(0, 0);
	Square* s = nullptr;
	for (i = 0; i < BOARD_SIDE_SIZE; i++)
	{
		if (isInBoard((x + xMoves[i]), (y + yMoves[i])))
		{
			
			possibleSquars.push_back(new Square((x + xMoves[i]), (y + yMoves[i]), nullptr));
		}
	}
	return possibleSquars;
}
