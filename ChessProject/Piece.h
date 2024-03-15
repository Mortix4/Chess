#pragma once

#include "Square.h"

#include <vector>
using std::vector;
class Square;

enum Color { WHITE, BLACK };
enum PieceType { ROOK, BISHOP, PAWN, KNIGHT, QUEEN, KING };
#define BOARD_SIDE_SIZE 8

class Piece
{
protected:
	int _x;
	int _y;
	Color _color;
	PieceType _type;


public:
	//Ctor
	Piece(Color c, int x, int y, PieceType type);

	//Dtor
	~Piece();

	//getters
	PieceType getType() const;
	Color getColor() const;
	int getX() const;
	int getY() const;

	//setters
	void setColor(Color color);
	void setPieceType(PieceType type);
	void setX(int x);
	void setY(int y);


	virtual vector<Square*> getPossibleMoves() = 0;

	bool isInBoard(int x, int y);

};
