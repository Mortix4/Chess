#include "Bishop.h"

Bishop::Bishop(Color c, int x, int y, PieceType type) : Piece(c, x, y, type)
{

}

Bishop::~Bishop()
{

}

vector<Square*> Bishop::getPossibleMoves()
{
	int x = _x, y = _y;
	int i = 0;
	vector<Square*> possibleSquars(0);

    Square tmp = (Square((x + i), (y + i), nullptr));
    Square* s = &tmp;

    for (i = 1; i < BOARD_SIDE_SIZE; i++) // first diagonal
    { 
        if (isInBoard((x + i), (y + i))) {
           
            possibleSquars.push_back(new Square((x + i), (y + i), nullptr));
        }
        if (isInBoard((x - i), (y - i))) {
            
            possibleSquars.push_back(new Square((x - i), (y - i), nullptr));
        }
    }
    
    for (i = 1; i < BOARD_SIDE_SIZE; i++) // second diagonal
    { 
        if (isInBoard((x + i), (y - i))) {
        
            possibleSquars.push_back(new Square((x + i), (y - i), nullptr));
        }
        if (isInBoard((x - i), (y + i))) {
          
            possibleSquars.push_back(new Square((x - i), (y + i), nullptr));
        }
    }

	return possibleSquars;
}