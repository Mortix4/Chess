#pragma once

#include <iostream>
#include "Square.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"


enum GameCode {
	VALID_MOVE, //0
	VALID_MOVE_AND_CHECK, //1
	INVALID_SRC_SQUARE_HAS_NO_CURRPLAYER_PIECE, //2
	INVALID_DST_SQUARE_HAS_CURR_PLAYER_PIECE,//3
	INVALID_THERE_WILL_BE_CHECK_ON_CURR_PLAYER,//4
	INVALID_ILLEGAL_SQUARES_INDEX, //5 -
	ILLEGAL_PIECE_MOVEMENT, //6
	INVALID_DST_SQUARE_EQUAL_SRC_SQUARE, //7
	VALID_MOVE_AND_CHECKMATE, // 8
	CHANGE_PAWN_TO_QUEEN_VALID, // 9
	SHORT_CASTLING,
	LONG_CASTLING
};

class Board
{
private:
	Square* _board[BOARD_SIDE_SIZE][BOARD_SIDE_SIZE];
	vector<Piece*> _whitePieces;
	vector<Piece*> _blackPieces;
	Color _currPlayerColor;

	bool _bKing;
	bool _wKing;
	bool _wlr;
	bool _wrr;
	bool _blr;
	bool _brr;

	bool isSquareInSquaresVector(Square* sToFind, vector<Square*> sVector);

public:
	//Ctor
	Board();
	//Dtor
	~Board();

	//getters

	vector<Piece*> getWhitePieces() const;
	vector<Piece*> getBlackPieces() const;
	Color getCurrPlayerColor() const;

	Color getOpposingPlayerColor() const;
	Square* getSquareFromBoard(Square squareToFind) const;
	Square* getSquare(int x, int y) const;
	Piece* getPieceAt(Square* pos) const;

	//setters
	void setWhitePieces(vector<Piece*> whitePieces);
	void setBlackPieces(vector<Piece*> blackPieces);
	void setCurrPlayerColor(Color c);
	void setPieceAt(int x, int y, Piece* p);

	//Methods
	void movePiece(Square* origin, Square* dst);
	void removePieceFromBoard(int x, int y);
	bool isInCheck(Color color);
	bool isCheckmate(Color color);
	bool isMoveAllowed(int sourceRow, int sourceCol, int destRow, int destCol);
	void removePieceFromPieceVector(Piece* pieceToRemove);

	GameCode getMoveCode(int xSrc, int ySrc, int xDst, int yDst);
	std::string boardToString();

	void updateColorVectors();
	void delVector(vector<Square*> v);
};