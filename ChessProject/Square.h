#pragma once
#include "Piece.h"

class Piece;

class  Square
{
private:
	int _x;
	int _y;
	Piece* _piece;

public:
	//Ctor
	Square(int x, int y, Piece* piece = nullptr);
	//Dtor
	~Square();
	
	//getters
	int getX() const;
	int getY() const;
	Piece* getPiece() const;

	//setters
	void setX(int x);
	void setY(int y);
	void setPiece(Piece* p);

	//Methods
	bool isOccupied() const;
	void removePiece();

};
