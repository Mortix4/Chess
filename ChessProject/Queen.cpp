#include "Queen.h"


Queen::Queen(Color c, int x, int y, PieceType type) : Piece(c, x, y, type)
{

}

Queen::~Queen()
{

}

vector<Square*> Queen::getPossibleMoves()
{
    int x = getX(), y = getY();
    int i = 0;
    vector<Square*> possibleSquars(0);
    vector<Square*> possibleSquars2(0);
    Color c = this->getColor();

    //creating temp rook and bishop 
    Rook rTmp(c, x, y, ROOK);
    Bishop bTmp(c, x, y, BISHOP);

    //Queen possible moves are the possible moves of the rook and the bishop
    possibleSquars = rTmp.getPossibleMoves();
    possibleSquars2 = bTmp.getPossibleMoves();
    //connacting the vectors
    for (i = 0; i < possibleSquars2.size(); i++)
    {
        possibleSquars.push_back(possibleSquars2[i]);
    }

    return possibleSquars;
}