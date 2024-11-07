#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// List of words to guess from
const vector<string> WORDS = {"computer", "programming", "hangman", "algorithm", "science", "function", "variable"};

// Function to pick a random word from the list
string getRandomWord()
{
  srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
  int index = rand() % WORDS.size();
  return WORDS[index];
}

// Function to display the current state of the word being guessed
void displayWord(const string &word, const vector<bool> &guessedLetters)
{
  for (size_t i = 0; i < word.size(); ++i)
  {
    if (guessedLetters[i])
    {
      cout << word[i] << " ";
    }
    else
    {
      cout << "_ ";
    }
  }
  cout << endl;
}

// Function to check if the player has won
bool isWordGuessed(const vector<bool> &guessedLetters)
{
  return all_of(guessedLetters.begin(), guessedLetters.end(), [](bool b)
                { return b; });
}

int main()
{
  string wordToGuess = getRandomWord();                   // Word the player has to guess
  vector<bool> guessedLetters(wordToGuess.size(), false); // Track guessed letters
  int remainingGuesses = 6;                               // Set the number of allowed guesses
  vector<char> wrongGuesses;                              // Store incorrect guesses

  cout << "Welcome to Hangman!\n";
  cout << "Guess the word. You have " << remainingGuesses << " wrong attempts allowed.\n";

  while (remainingGuesses > 0)
  {
    displayWord(wordToGuess, guessedLetters);
    cout << "Wrong guesses: ";
    for (char c : wrongGuesses)
    {
      cout << c << " ";
    }
    cout << "\nRemaining guesses: " << remainingGuesses << endl;

    // Get the player's guess
    cout << "Enter a letter: ";
    char guess;
    cin >> guess;

    // Check if the letter is in the word
    bool found = false;
    for (size_t i = 0; i < wordToGuess.size(); ++i)
    {
      if (wordToGuess[i] == guess && !guessedLetters[i])
      {
        guessedLetters[i] = true;
        found = true;
      }
    }

    if (!found)
    {
      // If the letter was not found in the word, reduce guesses and add to wrong guesses
      if (find(wrongGuesses.begin(), wrongGuesses.end(), guess) == wrongGuesses.end())
      {
        wrongGuesses.push_back(guess);
        remainingGuesses--;
      }
      else
      {
        cout << "You already guessed that letter!\n";
      }
    }

    // Check if the player has won
    if (isWordGuessed(guessedLetters))
    {
      cout << "Congratulations! You guessed the word: " << wordToGuess << endl;
      return 0;
    }
  }

  // If the player has run out of guesses
  cout << "You've run out of guesses. The word was: " << wordToGuess << endl;
  cout << "Better luck next time!\n";

  return 0;
}
