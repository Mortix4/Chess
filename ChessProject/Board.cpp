#include "Board.h"

//Ctor
Board::Board()
{
	//init the board to all the square to a nullptr
	for (int i = 0; i < BOARD_SIDE_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIDE_SIZE; j++)
		{
			Square* s = new Square(j, i, nullptr);
			_board[i][j] = s;
		}
	}
	//putting all the pieces in the right spots
	//Initialize white pieces
	Piece* p = new Rook(WHITE, 0, 0, ROOK);
	_board[0][0]->setPiece(p);
	_board[0][1]->setPiece(new Knight(WHITE, 1, 0, KNIGHT));
	_board[0][2]->setPiece(new Bishop(WHITE, 2, 0, BISHOP));
	_board[0][3]->setPiece(new Queen(WHITE, 3, 0, QUEEN));
	_board[0][4]->setPiece(new King(WHITE, 4, 0, KING));
	_board[0][5]->setPiece(new Bishop(WHITE, 5, 0, BISHOP));
	_board[0][6]->setPiece(new Knight(WHITE, 6, 0, KNIGHT));
	_board[0][7]->setPiece(new Rook(WHITE, 7, 0, ROOK));
	for (int i = 0; i < 8; i++)//setting all the white pawns
	{
		_board[1][i]->setPiece(new Pawn(WHITE, i, 1, PAWN));
	}
	// Initialize black pieces
	_board[7][0]->setPiece(new Rook(BLACK, 0, 7, ROOK));
	_board[7][1]->setPiece(new Knight(BLACK, 1, 7, KNIGHT));
	_board[7][2]->setPiece(new Bishop(BLACK, 2, 7, BISHOP));
	_board[7][3]->setPiece(new Queen(BLACK, 3, 7, QUEEN));
	_board[7][4]->setPiece(new King(BLACK, 4, 7, KING));
	_board[7][5]->setPiece(new Bishop(BLACK, 5, 7, BISHOP));
	_board[7][6]->setPiece(new Knight(BLACK, 6, 7, KNIGHT));
	_board[7][7]->setPiece(new Rook(BLACK, 7, 7, ROOK));
	for (int i = 0; i < 8; i++)//setting all the black pawns
	{
		_board[6][i]->setPiece(new Pawn(BLACK, i, 6, PAWN));
	}
	//white and black pieces vector Initializing
	for (int i = 0; i < BOARD_SIDE_SIZE; i++)
	{
		_whitePieces.push_back(_board[0][i]->getPiece());
		_blackPieces.push_back(_board[7][i]->getPiece());
		_whitePieces.push_back(_board[1][i]->getPiece());//white pawns
		_blackPieces.push_back(_board[6][i]->getPiece());//black pawns
	}
	_currPlayerColor = WHITE;


	_bKing = true;
	_wKing = true;
	_wlr = true;
	_wrr = true;
	_blr = true;
	_brr = true;
}

//Dtor
Board::~Board()
{
	for (int i = 0; i < BOARD_SIDE_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIDE_SIZE; j++)
		{
			delete _board[i][j];
		}
	}
}

//getters
vector<Piece*> Board::getWhitePieces() const
{
	return _whitePieces;
}
vector<Piece*> Board::getBlackPieces() const
{
	return _blackPieces;
}
Color Board::getCurrPlayerColor() const
{
	return _currPlayerColor;
}

Color Board::getOpposingPlayerColor() const
{
	if (_currPlayerColor == WHITE) {
		return BLACK;
	}
	return WHITE;
}
Square* Board::getSquareFromBoard(Square squareToFind) const // function to get a square from the board, gets a square that contain the x and y
{
	int x = squareToFind.getX(), y = squareToFind.getY();
	return (_board[y][x]);

}
Square* Board::getSquare(int x, int y) const
{
	return(_board[y][x]);
}
Piece* Board::getPieceAt(Square* pos) const
{
	int x = pos->getX(), y = pos->getY();
	return (_board[y][x]->getPiece());
}

//setters
void Board::setWhitePieces(vector<Piece*> whitePieces)
{
	_whitePieces = whitePieces;
}
void Board::setBlackPieces(vector<Piece*> blackPieces)
{
	_blackPieces = blackPieces;
}
void Board::setCurrPlayerColor(Color c)
{
	_currPlayerColor = c;
}
void Board::setPieceAt(int x, int y, Piece* p)//put a piece int the board at x, y
{
	_board[y][x]->setPiece(p);
}


//Methods
bool Board::isInCheck(Color color)
{
	Square tmp = Square(0, 0, nullptr);
	Square* kingSquare = &tmp;
	kingSquare->setPiece(nullptr);
	bool temp = false;
	if (color == WHITE)//white
	{
		for (size_t i = 0; i < _whitePieces.size(); i++)
		{
			if (_whitePieces[i]->getColor() == WHITE && _whitePieces[i]->getType() == KING)
			{
				kingSquare->setX(_whitePieces[i]->getX());
				kingSquare->setY(_whitePieces[i]->getY());
				kingSquare->setPiece(_whitePieces[i]);
				break;
			}
		}


		for (int i = 0; i < _blackPieces.size(); i++)
		{
			if (_blackPieces[i]->getType() == PAWN)
			{
				temp = ((Pawn*)_blackPieces[i])->getFirstMove();
			}
			if (isSquareInSquaresVector(kingSquare, _blackPieces[i]->getPossibleMoves()))
			{
				if (isMoveAllowed(_blackPieces[i]->getX(), _blackPieces[i]->getY(), kingSquare->getX(), kingSquare->getY()))
				{
					return true;
				}
			}
			if (_blackPieces[i]->getType() == PAWN)
			{
				((Pawn*)_blackPieces[i])->setFirstMove(temp);
			}
		}

	}
	else//black
	{
		for (size_t i = 0; i < _blackPieces.size(); i++)
		{
			if (_blackPieces[i]->getColor() == BLACK && _blackPieces[i]->getType() == KING)
			{
				kingSquare->setX(_blackPieces[i]->getX());
				kingSquare->setY(_blackPieces[i]->getY());
				kingSquare->setPiece(_blackPieces[i]);
				break;
			}
		}

		for (int i = 0; i < _whitePieces.size(); i++)
		{
			if (_whitePieces[i]->getType() == PAWN)
			{
				temp = ((Pawn*)_whitePieces[i])->getFirstMove();
			}
			if (isSquareInSquaresVector(kingSquare, _whitePieces[i]->getPossibleMoves()))
			{
				if (isMoveAllowed(_whitePieces[i]->getX(), _whitePieces[i]->getY(), kingSquare->getX(), kingSquare->getY()))
				{
					return true;
				}
			}
			if (_whitePieces[i]->getType() == PAWN)
			{
				((Pawn*)_whitePieces[i])->setFirstMove(temp);
			}
		}

	}

	return false;
}
void Board::removePieceFromBoard(int x, int y)
{
	_board[y][x]->removePiece();
}
bool Board::isSquareInSquaresVector(Square* sToFind, vector<Square*> sVector)
{
	int i = 0;
	for (i = 0; i < sVector.size(); i++)
	{
		if (sToFind->getX() == sVector[i]->getX() && sToFind->getY() == sVector[i]->getY())
		{
			return true;
		}
	}
	return false;
}
bool Board::isMoveAllowed(int srcX, int srcY, int dstX, int dstY)
{
	Square s = Square(srcX, srcY);
	Square* ss = &s;

	Piece* sourcePiece = getPieceAt(ss);

	s = Square(dstX, dstY);
	ss = &s;
	Piece* destPiece = getPieceAt(ss);
	int yDiff = 0;
	int xDiff = 0;

	switch (sourcePiece->getType())
	{
	case ROOK:
	{
		// A rook can move horizontally or vertically
		yDiff = std::abs(dstY - srcY);
		xDiff = std::abs(dstX - srcX);

		// Check if there are any pieces blocking the path from the source to the destination
		// You can do this by iterating through the squares between the source and destination and checking if they are occupied
		if (yDiff == 0)
		{
			// The rook is moving horizontally
			for (int i = std::min(srcX, dstX) + 1; i < std::max(srcX, dstX); i++)
			{
				if (_board[srcY][i]->isOccupied())
				{
					return false; // There is a piece blocking the path, so the move is not allowed
				}
			}
		}
		else
		{
			// The rook is moving vertically
			for (int i = std::min(srcY, dstY) + 1; i < std::max(srcY, dstY); i++)
			{
				if (_board[i][srcX]->isOccupied())
				{
					return false; // There is a piece blocking the path,
				}
			}
		}
		break;
	}
	case BISHOP:
	{
		yDiff = std::abs(dstY - srcY);
		xDiff = std::abs(dstX - srcX);
		int tx = srcX, ty = srcY;
		if (dstY < srcY && dstX < srcX) // going down left
		{
			while (tx != dstX && ty != dstY)
			{
				tx--;
				ty--;
				if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
				{
					return false;
				}
			}
		}
		else if (dstY > srcY && dstX < srcX) // up left
		{
			while (tx != dstX && ty != dstY)
			{
				tx--;
				ty++;
				if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
				{
					return false;
				}
			}
		}
		else if (dstY < srcY && dstX > srcX) // down right
		{
			while (tx != dstX && ty != dstY)
			{
				tx++;
				ty--;
				if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
				{
					return false;
				}
			}
		}
		else if (dstY > srcY && dstX > srcX) // up right 
		{
			while (tx != dstX && ty != dstY)
			{
				tx++;
				ty++;
				if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
				{
					return false;
				}
			}
		}

		return true;
		break;
	}
	case QUEEN:
	{
		//ROOK
		// A rook can move horizontally or vertically
		yDiff = std::abs(dstY - srcY);
		xDiff = std::abs(dstX - srcX);

		// Check if there are any pieces blocking the path from the source to the destination
		// You can do this by iterating through the squares between the source and destination and checking if they are occupied
		if (yDiff == 0)
		{
			// The rook is moving horizontally
			for (int i = std::min(srcX, dstX) + 1; i < std::max(srcX, dstX); i++)
			{
				if (_board[srcY][i]->isOccupied())
				{
					return false; // There is a piece blocking the path, so the move is not allowed
				}
			}
		}
		else if (xDiff == 0)
		{
			// The rook is moving vertically
			for (int i = std::min(srcY, dstY) + 1; i < std::max(srcY, dstY); i++)
			{
				if (_board[i][srcX]->isOccupied())
				{
					return false; // There is a piece blocking the path,
				}
			}
		}
		else//BISHOP
		{
			yDiff = std::abs(dstY - srcY);
			xDiff = std::abs(dstX - srcX);
			int tx = srcX, ty = srcY;
			if (dstY < srcY && dstX < srcX) // going down left
			{
				while (tx != dstX && ty != dstY)
				{
					tx--;
					ty--;
					if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
					{
						return false;
					}
				}
			}
			else if (dstY > srcY && dstX < srcX) // up left
			{
				while (tx != dstX && ty != dstY)
				{
					tx--;
					ty++;
					if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
					{
						return false;
					}
				}
			}
			else if (dstY < srcY && dstX > srcX) // down right
			{
				while (tx != dstX && ty != dstY)
				{
					tx++;
					ty--;
					if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
					{
						return false;
					}
				}
			}
			else if (dstY > srcY && dstX > srcX) // up right 
			{
				while (tx != dstX && ty != dstY)
				{
					tx++;
					ty++;
					if (_board[ty][tx]->isOccupied() && tx != dstX && ty != dstY)
					{
						return false;
					}
				}
			}
		}
		return true;
		break;
	}
	case PAWN:
	{
		yDiff = dstY - srcY;
		xDiff = dstX - srcX;
		if (sourcePiece->getColor() == BLACK)
		{
			// White pawns move upwards on the board
			if (yDiff == -1)
			{
				// Pawns can move forward one square if it is unoccupied
				if (xDiff == 0 && !_board[dstY][dstX]->isOccupied())
				{
					return true;
				}
				// Pawns can capture pieces on the diagonals
				else if (std::abs(xDiff) == 1 && _board[dstY][dstX]->isOccupied())
				{
					return true;
				}
			}
			// Pawns can move two squares forward on their first move
			else if (yDiff == -2 && !_board[dstY][dstX]->isOccupied() && !_board[srcY - 1][srcX]->isOccupied())
			{
				return true;
			}
		}
		else { // WHITE
			if (yDiff == 1) {
				// Pawns can move forward one square if it is unoccupied
				if (xDiff == 0 && !_board[dstY][dstX]->isOccupied())
				{
					return true;
				}
				// Pawns can capture pieces on the diagonals
				else if (std::abs(xDiff) == 1 && _board[dstY][dstX]->isOccupied())
				{
					return true;
				}
			}
			// Pawns can move two squares forward on their first move
			else if (yDiff == 2 && !_board[dstY][dstX]->isOccupied() && !_board[srcY + 1][srcX]->isOccupied())
			{
				return true;
			}
		}
		return false; // The move is not valid
		break;
	}
	default://king || knight
	{
		return true;
	}
	}
}

GameCode Board::getMoveCode(int xSrc, int ySrc, int xDst, int yDst)
{
	GameCode code = VALID_MOVE;

	//checking if the src and dst are on the board
	if (xSrc >= BOARD_SIDE_SIZE || ySrc >= BOARD_SIDE_SIZE || xDst >= BOARD_SIDE_SIZE || yDst >= BOARD_SIDE_SIZE || xSrc < 0 || ySrc < 0 || xDst < 0 || yDst < 0)
	{
		return INVALID_ILLEGAL_SQUARES_INDEX;
	}

	//checking if src = dst
	if (xSrc == xDst && ySrc == yDst)
	{
		return INVALID_DST_SQUARE_EQUAL_SRC_SQUARE;
	}

	//src square and dst square
	Square* sSrc = getSquare(xSrc, ySrc);
	Square* sDst = getSquare(xDst, yDst);

	vector<Square*> pieceMovesVector(0);

	//temps for saving info
	Piece* srcPieceTemp = nullptr;
	Piece* dstPieceTemp = nullptr;
	vector<Piece*> wPieces(0);
	vector<Piece*> bPieces(0);

	int x = 0, y = 0, i = 0, j = 0;

	// if src square is empty
	if (sSrc->isOccupied() == false) {
		return INVALID_SRC_SQUARE_HAS_NO_CURRPLAYER_PIECE;
	}

	// if src has enemy piece (You cant move your enemy pieces)
	if (sSrc->getPiece()->getColor() != _currPlayerColor) {
		return INVALID_SRC_SQUARE_HAS_NO_CURRPLAYER_PIECE;
	}

	// if src has enemy piece (You cant move your enemy pieces)
	if (sSrc->getPiece()->getColor() != _currPlayerColor) {
		return INVALID_SRC_SQUARE_HAS_NO_CURRPLAYER_PIECE;
	}


	//checking if the dst square have the currect player piece
	if (sDst->isOccupied()) {
		if (sDst->getPiece()->getColor() == _currPlayerColor) //dst has same  color piece
		{
			return INVALID_DST_SQUARE_HAS_CURR_PLAYER_PIECE;
		}
	}

	if (sSrc->getPiece()->getType() == KING)
	{
		if (_currPlayerColor == WHITE && _wKing)
		{
			if (xDst == 6 && yDst == 0 && _wrr) //short right
			{
				if (isMoveAllowed(7, 0, xSrc, ySrc))
				{
					return SHORT_CASTLING;
				}
			}
			else if (xDst == 2 && yDst == 0 && _wlr) // long left
			{
				if (isMoveAllowed(0, 0, xSrc, ySrc))
				{
					return LONG_CASTLING;
				}
			}
		}
		else if (_currPlayerColor == BLACK && _bKing)
		{
			if (xDst == 6 && yDst == 7 && _brr) //short right
			{
				if (isMoveAllowed(7, 7, xSrc, ySrc))
				{
					return SHORT_CASTLING;
				}
			}
			else if (xDst == 2 && yDst == 7 && _blr) // long left
			{
				if (isMoveAllowed(0, 7, xSrc, ySrc))
				{
					return LONG_CASTLING;
				}
			}
		}
	}


	pieceMovesVector = sSrc->getPiece()->getPossibleMoves();

	// checking if its an illeagal movement
	if (isSquareInSquaresVector(sDst, pieceMovesVector) == false)
	{
		return ILLEGAL_PIECE_MOVEMENT;
	}


	if (isCheckmate(WHITE) || isCheckmate(BLACK))
	{
		return VALID_MOVE_AND_CHECKMATE;
	}

	//saving info

	//wPieces = _whitePieces;
	//bPieces = _blackPieces;
	for (i = 0; i < _whitePieces.size(); i++)
	{
		wPieces.push_back(_whitePieces[i]);
	}
	for (i = 0; i < _blackPieces.size(); i++)
	{
		bPieces.push_back(_blackPieces[i]);
	}

	srcPieceTemp = sSrc->getPiece();
	dstPieceTemp = sDst->getPiece();
	code = VALID_MOVE;


	if (isMoveAllowed(xSrc, ySrc, xDst, yDst) == false) //checking if move is not legal
	{
		return ILLEGAL_PIECE_MOVEMENT;
	}

	movePiece(sSrc, sDst); //moving the piece (removing dst piece if there is one)

	//checking if there will be self check
	if (isInCheck(_currPlayerColor))
	{
		//redoing the move (ctrl z)

		_whitePieces = wPieces;
		_blackPieces = bPieces;
		sSrc->setPiece(srcPieceTemp);
		sDst->setPiece(dstPieceTemp);
		if (sSrc->getPiece())
		{
			sSrc->getPiece()->setX(xSrc);
			sSrc->getPiece()->setY(ySrc);
		}
		if (sDst->getPiece())
		{
			sDst->getPiece()->setX(xDst);
			sDst->getPiece()->setY(yDst);
		}
		code = INVALID_THERE_WILL_BE_CHECK_ON_CURR_PLAYER;
		return code;
	}
	if (_board[yDst][xDst]->getPiece()->getType() == PAWN)
	{
		if (_currPlayerColor == WHITE && yDst == 7)
		{
			delete _board[yDst][xDst]->getPiece();
			_board[yDst][xDst]->setPiece(new Queen(WHITE, xDst, yDst, QUEEN));
			_currPlayerColor = getOpposingPlayerColor();
			return CHANGE_PAWN_TO_QUEEN_VALID;
		}
		else if (_currPlayerColor == BLACK && yDst == 0)//black
		{
			delete _board[yDst][xDst]->getPiece();
			_board[yDst][xDst]->setPiece(new Queen(BLACK, xDst, yDst, QUEEN));
			_currPlayerColor = getOpposingPlayerColor();
			return CHANGE_PAWN_TO_QUEEN_VALID;
		}
	}

	
	/*if (srcPieceTemp->getType() ==  || dstPieceTemp->getType() == )
	{
		_wKing = false;
	}
	else if (sSrc->getPiece()->getType() == KING && _currPlayerColor == BLACK)
	{
		_bKing = false;
	}
	if (sSrc->getPiece()->getType() == ROOK || sDst->getPiece()->getType() == ROOK)
	{

	}*/


	if (isCheckmate(WHITE) || isCheckmate(BLACK))
	{
		return VALID_MOVE_AND_CHECKMATE;
	}
	else if (isInCheck(getOpposingPlayerColor())) //checking if there is now check on opponant
	{
		code = VALID_MOVE_AND_CHECK;
	}

	_currPlayerColor = getOpposingPlayerColor();
	return code;
}
void Board::movePiece(Square* origin, Square* dst)
{
	int i = 0;

	if (dst->isOccupied()) // if there is a piece at the dst than removing it
	{
		//removing the piece from his color vector
		removePieceFromPieceVector(dst->getPiece());

		removePieceFromBoard(dst->getX(), dst->getY());
	}

	setPieceAt(dst->getX(), dst->getY(), origin->getPiece()); // putting the piece in new place
	removePieceFromBoard(origin->getX(), origin->getY()); //removing the piece from the old place
	//updating the piece location
	_board[dst->getY()][dst->getX()]->getPiece()->setX(dst->getX());
	_board[dst->getY()][dst->getX()]->getPiece()->setY(dst->getY());

	//updating the piece in the vector
	updateColorVectors();
}


void Board::removePieceFromPieceVector(Piece* pieceToRemove)
{
	int i = 0;
	if (pieceToRemove->getColor() == WHITE)
	{
		for (i = 0; i < _whitePieces.size(); i++)
		{
			if (_whitePieces[i]->getX() == pieceToRemove->getX() && _whitePieces[i]->getY() == pieceToRemove->getY())
			{
				_whitePieces.erase(_whitePieces.begin() + i); //removeing the piece
				continue;
			}
		}
	}
	else
	{
		for (i = 0; i < _blackPieces.size(); i++)
		{
			if (_blackPieces[i]->getX() == pieceToRemove->getX() && _blackPieces[i]->getY() == pieceToRemove->getY())
			{
				_blackPieces.erase(_blackPieces.begin() + i); //removeing the piece
				continue;
			}
		}
	}
}

void Board::delVector(vector<Square*> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		delete(v[i]);
	}
}


void Board::updateColorVectors()
{
	vector<Piece*> w(0);
	vector<Piece*> b(0);

	for (int i = 0; i < BOARD_SIDE_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIDE_SIZE; j++)
		{
			if (_board[i][j]->isOccupied())
			{
				if (_board[i][j]->getPiece()->getColor() == WHITE)
				{
					w.push_back(_board[i][j]->getPiece());
				}
				else if (_board[i][j]->getPiece()->getColor() == BLACK)
				{
					b.push_back(_board[i][j]->getPiece());
				}
			}
		}
	}
	_whitePieces = w;
	_blackPieces = b;
}

std::string Board::boardToString()
{
	std::string b = "";

	for (int i = 0; i < BOARD_SIDE_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIDE_SIZE; j++)
		{

			Piece* piece = getPieceAt(_board[i][j]);
			if (piece)//not null
			{
				Color c = piece->getColor();
				switch (piece->getType())
				{
				case ROOK:
					if (c == WHITE)
					{
						b += "R";
						break;
					}
					b += "r";
					break;

				case PAWN:
					if (c == WHITE)
					{
						b += "P";
						break;
					}
					b += "p";
					break;

				case KING:
					if (c == WHITE)
					{
						b += "K";
						break;
					}
					b += "k";
					break;

				case QUEEN:
					if (c == WHITE)
					{
						b += "Q";
						break;
					}
					b += "q";
					break;

				case KNIGHT:
					if (c == WHITE)
					{
						b += "N";
						break;
					}
					b += "n";
					break;

				case BISHOP:
					if (c == WHITE)
					{
						b += "B";
						break;
					}
					b += "b";
					break;
				}
			}
			else
			{
				b += "#";
			}

		}
	}

	//current turn color
	if (_currPlayerColor == WHITE)
	{
		b += "0";
	}
	else
	{
		b += "1";
	}
	return b;
}

bool Board::isCheckmate(Color color)
{
	/*
	if (!isInCheck(color))
	{
		return false;
	}

	//we have to check three things 1.if the king can move//2.if any friend piece can eat the attacker//3.if any friend piece can block the attacker move
	bool flag = true;
	Square tmp = Square(0, 0, nullptr);
	Square* kingSquare = &tmp;
	vector<Square*> v(0);
	if (color == WHITE)//white
	{
		for (size_t i = 0; i < _whitePieces.size(); i++)
		{
			if (_whitePieces[i]->getColor() == WHITE && _whitePieces[i]->getType() == KING)
			{
				kingSquare->setX(_whitePieces[i]->getX());
				kingSquare->setY(_whitePieces[i]->getY());
				kingSquare->setPiece(_whitePieces[i]);
				break;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < _blackPieces.size(); i++)
		{
			if (_blackPieces[i]->getColor() == BLACK && _blackPieces[i]->getType() == KING)
			{
				kingSquare->setX(_blackPieces[i]->getX());
				kingSquare->setY(_blackPieces[i]->getY());
				kingSquare->setPiece(_blackPieces[i]);
				break;
			}
		}
	}
	v = kingSquare->getPiece()->getPossibleMoves();
	int xKing = kingSquare->getX(), yKing = kingSquare->getY();

	//1.if there is a possible move the checkmate turns into false
	for (size_t i = 0; i < v.size() && v[i] != nullptr; i++)
	{
		if (isMoveAllowed(xKing, yKing, v[i]->getX(), v[i]->getY()))
		{
			flag = false;
			break;
		}
	}

	//2,3check if any white piece can block or eat the attacker(the one that is making the checkmate)
	if (color == WHITE)
	{
		vector<Square*> curr(0);
		vector<Square*> currF(0);
		vector<Piece*> friends = getWhitePieces();
		vector<Piece*> attackers = getBlackPieces();
		int Xattacker, Yattacker;
		Piece* fake;
		//finding the attacker piece(the piece that is making the checkmate)
		for (size_t i = 0; i < attackers.size(); i++)
		{
			curr = attackers[i]->getPossibleMoves();
			for (size_t j = 0; j < curr.size(); j++)
			{
				if (curr[j]->getX() == xKing && curr[j]->getY() == yKing)
				{
					Xattacker = curr[j]->getX();
					Yattacker = curr[j]->getY();
					break;
				}
			}
		}

		//2,3
		for (size_t i = 0; i < friends.size(); i++)
		{
			currF = friends[i]->getPossibleMoves();
			for (size_t j = 0; j < currF.size(); j++)
			{
				//if the piece isn't null we have to check if it can eat it and its the attacker
				if (currF[j]->getPiece() != nullptr)
				{
					//2.check if the friends pieces can eat the attacker
					if (currF[j]->getX() == Xattacker && currF[j]->getY() == Yattacker)
					{
						flag = false;
						break;
					}
				}
				//if the piece is null we have to check if it can block the attacker from eating the king
				else
				{
					fake = friends[i];
					//putting the fake piece on the current possible move so we check if it can block the attacker
					_board[currF[j]->getX()][currF[j]->getY()]->setPiece(fake);


					//2.check if the friends pieces can block the attacker(by checking if the attacker can eat the king)
					if (!isMoveAllowed(Xattacker, Yattacker, xKing, yKing))
					{
						flag = false;
					}

					//removing the fake piece from its place
					_board[currF[j]->getX()][currF[j]->getY()]->setPiece(nullptr);
				}
			}
			if (flag == false)
			{
				break;
			}
		}
		delVector(currF);
		delVector(curr);
	}



	//2,3 check if any black piece can block or eat the attacker(the one that is making the checkmate)
	else
	{
		vector<Square*> curr(0);
		vector<Square*> currF(0);
		vector<Piece*> friends = getBlackPieces();
		vector<Piece*> attackers = getWhitePieces();
		int Xattacker, Yattacker;
		Piece* fake;
		//finding the attacker piece(the piece that is making the checkmate)
		for (size_t i = 0; i < attackers.size(); i++)
		{
			curr = attackers[i]->getPossibleMoves();
			for (size_t j = 0; j < curr.size(); j++)
			{
				if (curr[j]->getX() == xKing && curr[j]->getY() == yKing)
				{
					Xattacker = curr[j]->getX();
					Yattacker = curr[j]->getY();
					break;
				}
			}
		}

		//2,3
		for (size_t i = 0; i < friends.size(); i++)
		{
			currF = friends[i]->getPossibleMoves();
			for (size_t j = 0; j < currF.size(); j++)
			{
				//if the piece isn't null we have to check if it can eat it and its the attacker
				if (currF[j]->getPiece() != nullptr)
				{
					//2.check if the friends pieces can eat the attacker
					if (currF[j]->getX() == Xattacker && currF[j]->getY() == Yattacker)
					{
						flag = false;
						break;
					}
				}
				//if the piece is null we have to check if it can block the attacker from eating the king
				else
				{
					fake = friends[i];
					//putting the fake piece on the current possible move so we check if it can block the attacker
					_board[currF[j]->getX()][currF[j]->getY()]->setPiece(fake);


					//2.check if the friends pieces can block the attacker(by checking if the attacker can eat the king)
					if (!isMoveAllowed(Xattacker, Yattacker, xKing, yKing))
					{
						flag = false;
					}

					//moving the fake piece from its place
					_board[currF[j]->getX()][currF[j]->getY()]->setPiece(nullptr);

				}
			}
			if (flag == false)
			{
				break;
			}
		}
		delVector(currF);
		delVector(curr);
	}

	delVector(v);
	return flag;
	*/
return false;
}