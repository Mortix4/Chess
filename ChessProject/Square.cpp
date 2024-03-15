#include "Square.h"


//Ctor
Square::Square(int x, int y, Piece* piece)
{
	_x = x;
	_y = y;
	_piece = piece;
}

//Dtor
Square::~Square()
{

}

//getters
int Square::getX() const
{
	return _x;
}

int Square::getY() const
{
	return _y;
}

Piece* Square::getPiece() const
{
	return _piece;
}

//setters
void Square::setX(int x)
{
	_x = x;
}

void Square::setY(int y)
{
	_y = y;
}

void Square::setPiece(Piece* p)
{
	_piece = p;
}

//Methods
bool Square::isOccupied() const // returns true if there is piece in square else return false
{
	return _piece != nullptr;
}

void Square::removePiece() // replace pieace with nullptr
{
	_piece = nullptr;
}