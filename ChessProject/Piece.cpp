#include "Piece.h"


//Ctor
Piece::Piece(Color c, int x, int y, PieceType type)
{
	_color = c;
	_type = type;
	_x = x;
	_y = y;
}

//Dtor
Piece::~Piece()
{

}

//getters
PieceType Piece::getType() const
{
	return _type;
}

Color Piece::getColor() const
{
	return _color;
}

int Piece::getX() const
{
	return _x;
}

int Piece::getY()const
{
	return _y;
}

//setters
void Piece::setX(int x)
{
	_x = x;
}

void Piece::setY(int y)
{
	_y = y;
}

void Piece::setColor(Color color)
{
	_color = color;
}

void Piece::setPieceType(PieceType type)
{
	_type = type;
}


bool Piece::isInBoard(int x, int y)
{
	if (x < BOARD_SIDE_SIZE && y < BOARD_SIDE_SIZE)
	{
		return true;
	}
	return false;
}

