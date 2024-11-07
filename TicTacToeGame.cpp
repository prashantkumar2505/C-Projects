#include <iostream>
#include <vector>

using namespace std;

class TicTacToe
{
private:
  vector<char> board; // Represents the game board
  char currentPlayer; // Tracks current player (X or O)

public:
  TicTacToe() : board(9, ' '), currentPlayer('X')
  {
    for (int i = 0; i < 9; ++i)
    {
      board[i] = '1' + i; // Initialize board with numbers 1-9
    }
  }

  void displayBoard() const;   // Display current state of the board
  bool makeMove(int position); // Place player's mark at chosen position
  bool checkWin() const;       // Check for a winning combination
  bool isBoardFull() const;    // Check if the board is full (indicating a draw)
  void switchPlayer();         // Switch to the other player
  void playGame();             // Main game loop
};

void TicTacToe::displayBoard() const
{
  cout << "\n " << board[0] << " | " << board[1] << " | " << board[2] << endl;
  cout << "---|---|---" << endl;
  cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
  cout << "---|---|---" << endl;
  cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n"
       << endl;
}

bool TicTacToe::makeMove(int position)
{
  if (position < 1 || position > 9 || board[position - 1] == 'X' || board[position - 1] == 'O')
  {
    cout << "Invalid move. Try again.\n";
    return false;
  }
  board[position - 1] = currentPlayer;
  return true;
}

bool TicTacToe::checkWin() const
{
  const int WIN_COMBOS[8][3] = {
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
      {0, 3, 6},
      {1, 4, 7},
      {2, 5, 8}, // Columns
      {0, 4, 8},
      {2, 4, 6} // Diagonals
  };

  for (auto &combo : WIN_COMBOS)
  {
    if (board[combo[0]] == currentPlayer && board[combo[1]] == currentPlayer && board[combo[2]] == currentPlayer)
    {
      return true;
    }
  }
  return false;
}

bool TicTacToe::isBoardFull() const
{
  for (char cell : board)
  {
    if (cell != 'X' && cell != 'O')
    {
      return false;
    }
  }
  return true;
}

void TicTacToe::switchPlayer()
{
  currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void TicTacToe::playGame()
{
  cout << "Welcome to Tic Tac Toe!\n";
  displayBoard();

  while (true)
  {
    int move;
    cout << "Player " << currentPlayer << ", enter your move (1-9): ";
    cin >> move;

    if (makeMove(move))
    {
      displayBoard();

      // Check for win or draw
      if (checkWin())
      {
        cout << "Player " << currentPlayer << " wins!\n";
        break;
      }
      else if (isBoardFull())
      {
        cout << "It's a draw!\n";
        break;
      }
      switchPlayer(); // Switch to the next player
    }
  }
  cout << "Game over.\n";
}

int main()
{
  TicTacToe game;
  game.playGame();
  return 0;
}
