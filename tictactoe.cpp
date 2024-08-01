//*******************************************************************************************************
//
//		File:					Tic-Tac-Toe.cpp
//
//		This a tic tac toe game using minimax algorithm.
//	
//		Other files required: 
//			1.	none
//			
//*******************************************************************************************************

#include <iostream>
#include <vector>

//*******************************************************************************************************

using namespace std;

//*******************************************************************************************************

char winnerCheck(const char board[9]);
void displayBoard(const char board[9]);
int numEmptySquares(const char board[9]);
void displayInitialBoard();
bool compareSquares(char b1, char b2, char b3);
void askPlayerX(char board[]);
int minimax(char board[9], int depth, char player);
int bestMove(char board[9]);
char HUMAN = 'X';
char AI = 'O';

//*******************************************************************************************************

int main()
{
	char board[9] = 
	{ ' ',' ',' ',
	' ',' ',' ',
	' ',' ',' ' };
	displayInitialBoard();
	srand(time(0));
	int n;
	int unusedSquares = numEmptySquares(board);
	char playerTurn = AI;
	displayBoard(board);
	while ((unusedSquares > 0) && (winnerCheck(board) == ' '))
	{
		if (playerTurn == HUMAN)
		{
			askPlayerX(board);
			displayBoard(board);
			playerTurn = AI;
		}
		else
		{
			n = bestMove(board);
			board[n] = playerTurn;
			displayBoard(board);
			playerTurn = HUMAN;
		}
		--unusedSquares;
	}
	if (winnerCheck(board) == HUMAN)
	{
		cout << "Human won the game" << endl;
	}
	else if (winnerCheck(board) == AI)
	{
		cout << "AI won the game" << endl;
	}
	else
	{
		cout << "The game was tied" << endl;
	}
	return 0;
}

//*******************************************************************************************************

int numEmptySquares(const char board[9])
{
	int num = 0;
	for (int i = 0; i < 9; ++i)
	{
		if (board[i] == ' ')
		{
			++num;
		}
	}
	return num;
}

//*******************************************************************************************************

int minimax(char board[9], int depth, char player)
{
	char winner = winnerCheck(board);

	if (winner != ' ' || depth == 0) {
		if (winner == AI)
			return 1; 
		else if (winner == HUMAN)
			return -1; 
		else
			return 0; 
	}

	if (player == AI)
	{
		int bestScore = -100; 
		for (int i = 0; i < 9; ++i)
		{
			if (board[i] == ' ') 
			{
				board[i] = AI;
				int score = minimax(board, depth - 1, HUMAN);
				board[i] = ' ';
				bestScore = max(bestScore, score);
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 100; 
		for (int i = 0; i < 9; ++i) 
		{
			if (board[i] == ' ') 
			{
				board[i] = HUMAN;
				int score = minimax(board, depth - 1, AI);
				board[i] = ' ';
				bestScore = min(bestScore, score);
			}
		}
		return bestScore;
	}
}

//*******************************************************************************************************

int bestMove(char board[9])
{
	int score;
	int depth = 1;
	int result = 0;
	vector<int> winningOptions;
	vector<int> tieOptions;
	vector<int> losingOptions;
	for (int i = 0; i < 9; ++i)
	{
		if (board[i] == ' ')
		{
			board[i] = AI;
			char winner = winnerCheck(board);
			if (winner == AI)
			{
				winningOptions.push_back(i);
			}
			else
			{
				score = minimax(board, depth, HUMAN);
				board[i] = ' ';
				if (score == -1)
				{
					winningOptions.push_back(i);
				}
				else
					if (score == 0)
					{
						tieOptions.push_back(i);
					}
					else
						if (score == 1)
						{
							losingOptions.push_back(i);
						}
			}
			board[i] = ' ';
		}
	}
	int num;
	if (winningOptions.size() >= 1)
	{
		num = std::rand() % winningOptions.size();
		result = winningOptions[num];
	}
	else
		if (tieOptions.size() >= 1)
		{
			num = std::rand() % tieOptions.size();
			result = tieOptions[num];
		}
		else
			if (losingOptions.size() >= 1)
			{
				num = std::rand() % losingOptions.size();
				result = losingOptions[num];
			}
	return result;
}

//*******************************************************************************************************

void displayInitialBoard()
{
	cout << endl << endl;
	int row = 0;
	cout << "These are the numbers for each square:" << endl << endl;
	for (int i = 0; i < 3; ++i)
	{
		cout << " " << row << " | " << row + 1 << " | " << row + 2 << endl;
		if ((row == 0) || (row == 3))
		{
			cout << " ------------" << endl;
		}
		row += 3;
	}
	cout << endl << endl;
}

//*******************************************************************************************************

void displayBoard(const char board[9])
{
	cout << endl << endl;
	int row = 0;
	for (int i = 0; i < 3; ++i)
	{
		cout << " " << board[row] << " | " << board[row + 1] << " | " <<
			board[row + 2] << endl;
		if ((row == 0) || (row == 3))
		{
			cout << " -----------" << endl;
		}
		row += 3;
	}
	cout << endl << endl;
}

//*******************************************************************************************************

bool compareSquares(char b1, char b2, char b3)
{
	bool result = false;
	if ((b1 == b2) && (b2 == b3) && (b1 != ' '))
	{
		result = true;
	}
	return result;
}

//*******************************************************************************************************

char winnerCheck(const char board[9])
{
	char winner = ' ';
	int i = 0;
	do
	{
		if (compareSquares(board[i], board[i + 1], board[i + 2]))
		{
			winner = board[i];
		}
		i += 3;
	} 
	while ((i < 9) && (winner == ' '));
	if (winner == ' ')
	{
		i = 0;
		do
		{
			if (compareSquares(board[i], board[i + 3], board[i + 6]))
			{
				winner = board[i];
			}
			i += 1;
		} while ((i < 3) && (winner == ' '));
	}
	if (winner == ' ')
	{
		i = 0;
		if (compareSquares(board[0], board[4], board[8]))
		{
			winner = board[0];
		}
		else if (compareSquares(board[2], board[4], board[6]))
		{
			winner = board[2];
		}
	}
	return winner;
}

//*******************************************************************************************************

void askPlayerX(char board[])
{
	bool validChoice;
	int n;
	do
	{
		cout << "Enter a square number: ";
		cin >> n;
		if (board[n] == ' ')
		{
			validChoice = true;
			board[n] = 'X';
		}
		else
		{
			cout << endl << " Must choose an empty square" << endl
				<< endl;
			validChoice = false;
		}
	} while (validChoice == false);
}

//*******************************************************************************************************


