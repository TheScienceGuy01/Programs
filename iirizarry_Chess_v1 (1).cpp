/*
|===*
 * ========================================================================================
 *    Program: iirizarry_10-17-24_ChessProject_v1.2.cpp
 *    Name: Israel Irizarry
 *    Date Created:10/17/2024
 *
 *	  Purpose: This program is a way I practiced C++ and OOP. This script is a little more
 *       than half the length of my C program. It uses multiple classes and functions all
 *		 from learning OOP.
 *
 *    How to play: Player 1 starts and is the player with pieces labelled with a letter
 *        then a 0 (ex. player 1's pawns are P0). Player 2 has pieces labelled with a
 *        letter then a 1 (ex. player 2's pawns are P1).
 *
 *        Inputs are separate for each move.
 *		  For example:
				    a  b  c  d  e  f  g  h
				   _________________________
				8  |R0|N0|B0|K0|Q0|B0|N0|R0|
				7  |P0|P0|P0|P0|P0|P0|P0|P0|
				6  |__|__|__|__|__|__|__|__|
				5  |__|__|__|__|__|__|__|__|
				4  |__|__|__|__|__|__|__|__|
				3  |__|__|__|__|__|__|__|__|
				2  |P1|P1|P1|P1|P1|P1|P1|P1|
				1  |R1|N1|B1|K1|Q1|B1|N1|R1|
				   -------------------------
				============================================
				Enter x coordinate to move from: a
				Enter y coordinate to move from: 2

				Enter x coordinate to move to: a
				Enter y coordinate to move to: 3
 *
 *        ***NOTE*** Not all chess rules are incorportated in this program.
 *
 *    Versions:
 *        v1.0 - 10/17/2024 - Base script finished.
 *        v1.1 - 1/22/2025 - Added some comments and polished the game.
 *
 * ========================================================================================
|===*
*/
#include "CMakeProject1.h"
#include <vector>

using namespace std;

/*========================================================================================
*                                   Board Class
* This class handles board manipulation such as board display, piece movement confirming
* whether the game is over, and piece information for debugging.
* 
========================================================================================*/
class Board
{
	int width;
	int length;
	vector<pair<int, int>> grid;
	vector<string> gridDisplay;
	bool isOver = false;
	bool winningTeam = false;
	bool initialize = false;
public:

	Board(int w, int l)
		:width(w)
		, length(l)
	{
	}

	//Initializes the board.
	void initDefaults()
	{
		for (size_t i = 0; i < length; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				gridDisplay.push_back("__");
			}
		}

		for (size_t i = 0; i < length; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				grid.push_back({ j,i });
				//cout << "|" << j << " " << i;
			}
			//cout << "|\n";
		}

		if (initialize == true)
		{
			for (size_t i = 0; i < length; i++)
			{
				for (size_t j = 0; j < width; j++)
				{
					//grid.push_back({ j,i });
					cout << "|" << j << " " << i;
				}
				cout << "|\n";
			}
		}
		else 
		{
			initialize = true;
		}
	}

	//Checks if hte piece that wants to move can move.
	//Pieces can only move if the spot chosen is blank or is an enemy piece AND no other pieces are in the way according to each pieces movement set.
	bool movePiece(int x, int y, int currX, int currY, string piece, bool checkMove)
	{
		for (size_t i = 0; i < grid.size(); i++)
		{
			if (grid[i].first == x && grid[i].second == y)
			{
				if (gridDisplay[i] == "__" || (gridDisplay[i][1] != piece[1]))
				{
					for (size_t q = 0; q < grid.size(); q++)
					{
						if (grid[q].first == currX && grid[q].second == currY && checkMove == false)
						{
							gridDisplay[q] = "__";
						}
					}
					if (checkMove == false)
					{
						if (gridDisplay[i] == "K0")
						{
							isOver = true;
						}
						else if (gridDisplay[i] == "K1")
						{
							winningTeam = true;
							isOver = true;
						}
						gridDisplay[i] = piece;
						return true;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}

	//Identifies the winner of the game when prompted.
	bool gameOver()
	{
		if (isOver == true)
		{
			string winner = "";
			if (winningTeam == true) {
				winner = "Player 1";
			}
			else
			{
				winner = "Player 2";
			}
			cout << R"(
|===*
 * ======================================================================================== 
 *    
 *    GAME OVER!
 * 
 *    )"<<winner<<R"( wins!
 *    
 * ========================================================================================
|===*
)";
		}
		return isOver;
	}

	//Gets piece information for bug fixing.
	string getPiece(int x, int y)
	{
		for (size_t i = 0; i < grid.size(); i++)
		{
			if (grid[i].first == x && grid[i].second == y)
			{
				return gridDisplay[i];
			}
		}
		return "";
	}

	//Returns the size of the board for bug fixing.
	pair<int, int> size()
	{
		return { width, length };
	}

	vector<string> getGrid()
	{
		return gridDisplay;
	}

	//Prints the board each round with the changes made.
	void print()
	{
		vector<char> xAxis = {'a','b','c','d','e','f','g','h'};
		cout << "\n|=====================================================================\n";
		int count = 0;

		cout << "    a  b  c  d  e  f  g  h\n   _________________________\n";
		for (size_t i = 0; i < length; i++)
		{
			cout << length - i<<"  ";
			for (size_t j = 0; j < width; j++)
			{
				cout << "|" << gridDisplay[count];
				count += 1;
			}

			cout << "|\n";
		}
		cout << "   -------------------------\n";
	}
};

/*========================================================================================
*                                   Piece Class
* This class sets all piece's movement based on their type. This class also checks to see
* all possible moves the piece can make. This class also changes the turn when called.
*
========================================================================================*/
class Piece
{
	string pieceName = "TestPiece";
	string shownName = "TP";
	int team = -1;
	int currX = -1;
	int currY = -1;
	vector<pair<int, int>> possibleMoves;
	bool isInit1 = true;
	bool changeTurn = false;
public:
	Piece() {}

	Piece(string name, string shortName)
		: pieceName(name)
		, shownName(shortName)
	{
	}

	void getInfo()
	{
		cout << "\n=============================\nName: " << pieceName;
		cout << "\nInitialed Name: " << shownName;
		cout << "\nX and Y: " << currX << ", " << currY << "\n=============================\n";
	}

	pair<int, int> position()
	{
		return { currX, currY };
	}

	bool nextTurn()
	{
		return changeTurn;
	}

	void move(int x, int y, class Board& board, bool isInit)
	{
		bool didMove = false;
		possibleMoves.clear();

		//Initialies all pieces.
		if (isInit == true)
		{
			didMove = board.movePiece(x, y, currX, currY, shownName, false);
		}

		//Controls all King movement.
		if (pieceName == "King")
		{
			possibleMoves.push_back({ currX + 1, currY });
			possibleMoves.push_back({ currX - 1, currY });
			possibleMoves.push_back({ currX, currY + 1 });
			possibleMoves.push_back({ currX, currY - 1 });
			possibleMoves.push_back({ currX + 1, currY + 1 });
			possibleMoves.push_back({ currX - 1, currY - 1 });
			possibleMoves.push_back({ currX + 1, currY - 1 });
			possibleMoves.push_back({ currX - 1, currY + 1 });
		}

		//Controls rook and queen movement.
		if (pieceName == "Rook" || pieceName == "Queen")
		{

			for (size_t i = 1; i < board.size().first; i++)
			{
				if (board.getPiece(currX + i, currY) == "__")
				{
					possibleMoves.push_back({ currX + i, currY });

				}
				else
				{
					if (board.movePiece(currX + i, currY, currX, currY, shownName, true) == true)
					{
						possibleMoves.push_back({ currX + i, currY });

					}
					break;
				}
			}
			for (size_t i = 1; i < board.size().first; i++)
			{
				if (board.getPiece(currX - i, currY) == "__")
				{
					possibleMoves.push_back({ currX - i, currY });

				}
				else
				{
					if (board.movePiece(currX - i, currY, currX, currY, shownName, true) == true)
					{
						possibleMoves.push_back({ currX - i, currY });

					}
					break;
				}
			}
			for (size_t i = 1; i < board.size().second; i++)
			{
				if (board.getPiece(currX, currY - i) == "__")
				{
					possibleMoves.push_back({ currX, currY-i });
				}
				else
				{
					if (board.movePiece(currX, currY - i, currX, currY, shownName, true) == true)
					{
						possibleMoves.push_back({ currX, currY - i });
					}
					break;
				}
			}
			for (size_t i = 1; i < board.size().second; i++)
			{
				if (board.getPiece(currX, currY + i) == "__")
				{
					possibleMoves.push_back({ currX, currY + i });
				}
				else
				{
					if (board.movePiece(currX, currY + i, currX, currY, shownName, true) == true)
					{
						possibleMoves.push_back({ currX, currY + i });
					}
					break;
				}
			}
		}

		//Controls bishop and queen movement.
		if (pieceName == "Bishop" || pieceName == "Queen")
		{
			//bool stopChecks = false;
			for (size_t i = 1; i < board.size().first; i++)
			{
				if (board.getPiece(currX - i, currY - i) == "__")
				{
					possibleMoves.push_back({ currX - i, currY - i });
				}
				else {
					if (((board.movePiece(currX - i, currY - i, currX, currY, shownName, true) == true)))
					{
						possibleMoves.push_back({ currX - i, currY - i });
					}
					break;
				}
			}
			for (size_t i = 1; i < board.size().first; i++)
			{
				if (board.getPiece(currX + i, currY - i) == "__")
				{
					possibleMoves.push_back({ currX + i, currY - i });
				}
				else {
					if (((board.movePiece(currX + i, currY - i, currX, currY, shownName, true) == true)))
					{
						possibleMoves.push_back({ currX + i, currY - i });
					}
					break;
				}
			}
			for (size_t i = 1; i < board.size().first; i++)
			{
				if (board.getPiece(currX + i, currY + i) == "__")
				{
					possibleMoves.push_back({ currX + i, currY + i });
				}
				else {
					if (((board.movePiece(currX + i, currY + i, currX, currY, shownName, true) == true)))
					{
						possibleMoves.push_back({ currX + i, currY + i });
					}
					break;
				}
			}
			for (size_t i = 1; i < board.size().first; i++)
			{
				if (board.getPiece(currX - i, currY + i) == "__")
				{
					possibleMoves.push_back({ currX - i, currY + i });
				}
				else {
					if (((board.movePiece(currX - i, currY + i, currX, currY, shownName, true) == true)))
					{
						possibleMoves.push_back({ currX - i, currY + i });
					}
					break;
				}
			}
			
			
		}

		//Controls Pawn movement.
		if (pieceName == "Pawn")
		{

			if (shownName == "P0")
			{
				//cout << board.getPiece(currX, currY + 1) << " " << board.getPiece(currX, currY + 2);
				if (board.movePiece(currX, currY + 1, currX, currY, shownName, true) == true && board.getPiece(currX, currY + 1) == "__")
				{
					possibleMoves.push_back({ currX, currY + 1 });
				}
				if (board.movePiece(currX, currY + 2, currX, currY, shownName, true) == true && board.getPiece(currX, currY + 1) == "__" && isInit1 == true && board.getPiece(currX, currY + 2) == "__")
				{
					if (isInit == false)
					{
						isInit1 = false;
					}
					possibleMoves.push_back({ currX, currY + 2 });
				}
				if (board.movePiece(currX + 1, currY + 1, currX, currY, shownName, true) == true && board.getPiece(currX + 1, currY + 1) != "__")
				{
					possibleMoves.push_back({ currX + 1, currY + 1 });
				}
				if (board.movePiece(currX - 1, currY + 1, currX, currY, shownName, true) == true && board.getPiece(currX - 1, currY + 1) != "__")
				{
					possibleMoves.push_back({ currX - 1, currY + 1 });
				}
			}
			if (shownName == "P1")
			{
				if (board.movePiece(currX, currY - 1, currX, currY, shownName, true) == true && board.getPiece(currX, currY - 1) == "__")
				{
					possibleMoves.push_back({ currX, currY - 1 });
				}
				if (board.movePiece(currX, currY - 2, currX, currY, shownName, true) == true && board.getPiece(currX, currY - 1) == "__" && isInit1 == true && board.getPiece(currX, currY - 2) == "__")
				{
					if (isInit == false)
					{
						isInit1 = false;
					}
					possibleMoves.push_back({ currX, currY - 2 });
				}
				if (board.movePiece(currX - 1, currY - 1, currX, currY, shownName, true) == true && board.getPiece(currX - 1, currY - 1) != "__")
				{
					possibleMoves.push_back({ currX - 1, currY - 1 });
				}
				if (board.movePiece(currX + 1, currY - 1, currX, currY, shownName, true) == true && board.getPiece(currX + 1, currY - 1) != "__")
				{
					possibleMoves.push_back({ currX + 1, currY - 1 });
				}
			}
		}

		//Controls knight movement.
		if (pieceName == "Knight")
		{
			if (board.movePiece(currX + 2, currY - 1, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX + 2, currY - 1 });
			}
			if (board.movePiece(currX + 2, currY + 1, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX + 2, currY + 1 });
			}
			if (board.movePiece(currX - 2, currY - 1, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX - 2, currY - 1 });
			}
			if (board.movePiece(currX - 2, currY + 1, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX - 2, currY + 1 });
			}
			if (board.movePiece(currX + 1, currY - 2, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX + 1, currY - 2 });
			}
			if (board.movePiece(currX + 1, currY + 2, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX + 1, currY + 2 });
			}
			if (board.movePiece(currX - 1, currY - 2, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX - 1, currY - 2 });
			}
			if (board.movePiece(currX - 1, currY + 2, currX, currY, shownName, true) == true)
			{
				possibleMoves.push_back({ currX - 1, currY + 2 });
			}
		}

		//For every possible move, it checks with the board on whether there are any conflicts.
		for (size_t i = 0; i < possibleMoves.size(); i++)
		{
			//cout << "\nPM:" <<pieceName<<" " << possibleMoves[i].first << " " << possibleMoves[i].second << "  " << didMove;
			if ((x == possibleMoves[i].first && y == possibleMoves[i].second))
			{
				didMove = board.movePiece(x, y, currX, currY, shownName, false);
				break;
			}
		}

		//If no conflicts with the destination of the piece, then the move is executed. If there are conflicts, the turn does not change and the player has to try again.
		if (didMove == true || isInit == true)
		{
			currX = x;
			currY = y;
			changeTurn = true;
		}
		else
		{
			changeTurn = false;
			cout << "\n\n********************\n\nInvalid movement:\n\nYou need to move one of your pieces to a valid spot\nor you are trying to move a piece that is not yours.\n\n*******************\n";
		}
	}
};

/*========================================================================================
*                                   Main Class
* This class initializes the game, displays program information, and runs the main game
* loop. This includes taking user input for the other classes.
*
========================================================================================*/
int main()
{
	//Displays program information.
	cout << R"(
|===*
 * ======================================================================================== 
 *    
 *    Welcome to Chess made in C++! 
 *
 *    Name: Israel Irizarry
 *    Date Created:10/17/2024
 * 
 *	  Purpose: This program is a way I practiced C++ and OOP. This script is a little more
 *       than half the length of my C program. It uses multiple classes and functions all
 *		 from learning OOP.
 * 
 *    How to play: Player 1 starts and is the player with pieces labelled with a letter
 *        then a 0 (ex. player 1's pawns are P0). Player 2 has pieces labelled with a
 *        letter then a 1 (ex. player 2's pawns are P1).
 * 
 *        Inputs are separate for each move.
 *		  For example:
				    a  b  c  d  e  f  g  h
				   _________________________
				8  |R0|N0|B0|K0|Q0|B0|N0|R0|
				7  |P0|P0|P0|P0|P0|P0|P0|P0|
				6  |__|__|__|__|__|__|__|__|
				5  |__|__|__|__|__|__|__|__|
				4  |__|__|__|__|__|__|__|__|
				3  |__|__|__|__|__|__|__|__|
				2  |P1|P1|P1|P1|P1|P1|P1|P1|
				1  |R1|N1|B1|K1|Q1|B1|N1|R1|
				   -------------------------
				============================================
				Enter x coordinate to move from: a
				Enter y coordinate to move from: 2

				Enter x coordinate to move to: a
				Enter y coordinate to move to: 3
 *
 *        ***NOTE*** Not all chess rules are incorportated in this program.
 * 
 *    Versions:
 *        v1.0 - 10/17/2024 - Base script finished.
 *        v1.1 - 1/
 * 
 * ========================================================================================
|===*
)";

	//Populates and initializes pieces on the board.

	Board board(8, 8);
	board.initDefaults();

	bool teamTurn = false;

	vector<Piece> pieces;

	Piece King0("King", "K0");
	Piece King1("King", "K1");

	Piece Rook01("Rook", "R0");
	Piece Rook02("Rook", "R0");
	Piece Rook11("Rook", "R1");
	Piece Rook12("Rook", "R1");

	Piece Bishop11("Bishop", "B1");
	Piece Bishop12("Bishop", "B1");
	Piece Bishop01("Bishop", "B0");
	Piece Bishop02("Bishop", "B0");

	Piece Queen0("Queen", "Q0");
	Piece Queen1("Queen", "Q1");

	Piece Knight01("Knight", "N0");
	Piece Knight02("Knight", "N0");
	Piece Knight11("Knight", "N1");
	Piece Knight12("Knight", "N1");

	Piece Pawn01("Pawn", "P0");
	Piece Pawn02("Pawn", "P0");
	Piece Pawn03("Pawn", "P0");
	Piece Pawn04("Pawn", "P0");
	Piece Pawn05("Pawn", "P0");
	Piece Pawn06("Pawn", "P0");
	Piece Pawn07("Pawn", "P0");
	Piece Pawn08("Pawn", "P0");
	Piece Pawn11("Pawn", "P1");
	Piece Pawn12("Pawn", "P1");
	Piece Pawn13("Pawn", "P1");
	Piece Pawn14("Pawn", "P1");
	Piece Pawn15("Pawn", "P1");
	Piece Pawn16("Pawn", "P1");
	Piece Pawn17("Pawn", "P1");
	Piece Pawn18("Pawn", "P1");

	Pawn01.move(0, 1, board, true);
	Pawn02.move(1, 1, board, true);
	Pawn03.move(2, 1, board, true);
	Pawn04.move(3, 1, board, true);
	Pawn05.move(4, 1, board, true);
	Pawn06.move(5, 1, board, true);
	Pawn07.move(6, 1, board, true);
	Pawn08.move(7, 1, board, true);
	Pawn11.move(0, 6, board, true);
	Pawn12.move(1, 6, board, true);
	Pawn13.move(2, 6, board, true);
	Pawn14.move(3, 6, board, true);
	Pawn15.move(4, 6, board, true);
	Pawn16.move(5, 6, board, true);
	Pawn17.move(6, 6, board, true);
	Pawn18.move(7, 6, board, true);

	King0.move(3, 0, board, true);
	King1.move(3, 7, board, true);

	Queen0.move(4, 0, board, true);
	Queen1.move(4, 7, board, true);


	Rook01.move(0, 0, board, true);
	Rook02.move(7, 0, board, true);
	Rook11.move(0, 7, board, true);
	Rook12.move(7, 7, board, true);

	Bishop01.move(2, 0, board, true);
	Bishop02.move(5, 0, board, true);
	Bishop11.move(2, 7, board, true);
	Bishop12.move(5, 7, board, true);

	Knight01.move(1, 0, board, true);
	Knight02.move(6, 0, board, true);
	Knight11.move(1, 7, board, true);
	Knight12.move(6, 7, board, true);

	pieces.insert(pieces.end(), {King1, King0, Queen0, Queen1, Pawn01, Pawn02, Pawn03, Pawn04, Pawn05, Pawn06, Pawn07, Pawn08, Pawn11, Pawn12, Pawn13, Pawn14, Pawn15, Pawn16, Pawn17, Pawn18, Rook01, Rook02
		, Rook11, Rook12, Bishop01, Bishop02, Bishop11, Bishop12, Knight01, Knight02, Knight11, Knight12});

	board.print();

	int startY, endY, startX, endX;
	char startXChar, endXChar;
	vector<char> xAxis = { 'a','b','c','d','e','f','g','h' };

	//Main game loop until the game ends.
	while (board.gameOver() == false)
	{
		//Piece to move X value.
		cout << "============================================\nEnter x coordinate to move from: ";
		cin >> startXChar;

		bool isValid = false;

		for (char letter : xAxis) 
		{
			if (startXChar == letter)
			{
				isValid = true;
			}
		}

		//Checks to see the input was correct and valid.
		while (isValid == false || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Character not valid. Please enter an x coordinate to move from: ";
			cin >> startXChar;

			for (char letter : xAxis)
			{
				if (startXChar == letter)
				{
					isValid = true;
				}
			}
		}

		//Piece to move Y value.
		cout << "Enter y coordinate to move from: ";
		cin >> startY;

		//Checks to see the input was correct and valid.
		while (cin.fail() || startY > 8)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Character not valid. Please enter an y coordinate to move from: ";
			cin >> startY;
		}

		startY = (8 - startY);

		//Piece destination X value.
		cout << "\nEnter x coordinate to move to: ";
		cin >> endXChar;

		isValid = false;

		for (char letter : xAxis)
		{
			if (endXChar == letter)
			{
				isValid = true;
			}
		}

		//Checks to see the input was correct and valid.
		while (isValid == false || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Character not valid. Please enter an x coordinate to move from: ";
			cin >> endXChar;

			for (char letter : xAxis)
			{
				if (endXChar == letter)
				{
					isValid = true;
				}
			}
		}

		//Piece destination Y value.
		cout << "Enter y coordinate to move to: ";
		cin >> endY;

		//Checks to see the input was correct and valid.
		while (cin.fail() || endY > 8)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Character not valid. Please enter an y coordinate to move from: ";
			cin >> endY;
		}

		cout << "============================================";
		for (int i = 0; i < 8; i++)
		{
			if (xAxis[i] == startXChar)
			{
				startX = i;
			}
			if (xAxis[i] == endXChar)
			{
				endX = i;
			}
		}

		endY = 8 - endY;

		//Changes player turn.
		string pieceToMove = board.getPiece(startX, startY);
		if ((!pieceToMove.empty() && pieceToMove.back() == '0' && teamTurn == false) || (!pieceToMove.empty() && pieceToMove.back() == '1' && teamTurn == true))
		{
			for (int i = 0; i < pieces.size(); i++)
			{
				if (pieces[i].position().first == startX && pieces[i].position().second == startY)
				{
					pieces[i].move(endX, endY, board, false);
					if (pieces[i].nextTurn() == true)
					{
						teamTurn = !teamTurn;
						if (teamTurn == true)
						{
							cout << "\n\nPlayer 2's turn...\n";
						}
						else
						{
							cout << "\n\nPlayer 1's turn...\n";

						}
					}
					board.gameOver();
				}
			}
		}
		else
		{
			cout << "\n\n********************\n\nInvalid movement:\n\nYou need to move one of your pieces to a valid spot\nor you are trying to move a piece that is not yours.\n\n*******************\n";
			if (teamTurn == true)
			{
				cout << "\nStill player 2's turn...\n";
			}
			else
			{
				cout << "\nStill player 1's turn...\n";

			}
		}

		board.print();
	}

	return 0;
}
