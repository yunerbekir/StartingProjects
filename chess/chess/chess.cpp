// chess.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
#include "Figure.h"
#include "King.h"
#include "Board.h"

#include <fcntl.h>
#include <io.h>
#include <string>

using namespace std;


int main()
{
	static Board chessGame;
	chessGame.showMenu();
	
	/*Board b;
	b.newGame();
	b.visualizeBoard();
	/*_setmode(_fileno(stdout), _O_U16TEXT);
	//wchar_t s = "\x2654";
	//	wchar_t = "\x263a"
	wcout << L"\u14EC";
	return 0;
	*/
	
	return 0;
}

