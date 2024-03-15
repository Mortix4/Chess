///*
//This file servers as an example of how to use Pipe.h file.
//It is recommended to use the following code in your project,
//in order to read and write information from and to the Backend
//*/
//
//#include "Board.h"
//#include <iostream>
//
//using std::cout;
//using std::endl;
//using std::string;
//using std::cin;
//
//void main()
//{
//	Board board = Board();
//
//	while (true)
//	{
//		char st[2] = { 0 }, inp[5] = { 0 };
//		std::string s = "";
//		int srcX = 0, srcY = 0, dstX = 0, dstY = 0;
//		cout << "enter the pieces that you want to move: " << endl;//e2e4
//		cin >> inp;
//		srcX = inp[0] - 'a', srcY = inp[1] - '1', dstX = inp[2] - 'a', dstY = inp[3] - '1';
//		st[0] = board.getMoveCode(srcX, srcY, dstX, dstY) + '0';
//		cout << "CODE: " << st[0] << '\n' << "Board: " << endl;
//		s = board.boardToString();
//		for (int i = 0; i < BOARD_SIDE_SIZE; i++)
//		{
//			for (int j = 0; j < BOARD_SIDE_SIZE; j++)
//			{
//				cout << s[i * BOARD_SIDE_SIZE + j] << "\t";
//			}
//			cout << '\n';
//		}	
//	}
//}

/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include "Board.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	Board board = Board();
	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0"); // just example...

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{

		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		char st[3] = { 0 };
		int srcX = 4, srcY = 1, dstX = 4, dstY = 5, tmp =0;
		srcX = msgFromGraphics[0] - 'a', srcY = msgFromGraphics[1] - '1', dstX = msgFromGraphics[2] - 'a', dstY = msgFromGraphics[3] - '1';
		tmp = board.getMoveCode(srcX, srcY, dstX, dstY);
		if (tmp == 10)
		{
			st[0] = '1';
			st[1] = '0';
		}
		else if (tmp == 11)
		{
			st[0] = '1';
			st[1] = '1';
		}
		else
		{
			st[1] = 0;
			st[0] = tmp + '0';
			cout << "Code " << st[0] << endl;
		}
		strcpy_s(msgToGraphics, st); // msgToGraphics should contain the result of the operation

		/******* JUST FOR EREZ DEBUGGING ******/
		//int r = rand() % 10; // just for debugging......
		//msgToGraphics[0] = (char)(1 + '0');
		//msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/


		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}

