#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype> //for isalpha() and isupper()
 
using namespace std;

/******************************************************************************************************************************
Author: Eylül Öykü Þen 

Student ID: 28297

Date: 11/03/2022

This program demonstrates a different version of the game Wordle, the new version is named as SWordle. Given a specified number of 
attempts and the length of the secret word, user is expected to guess the secret word correctly. After some sequential input checks,
the valid guesses of the user are shown in a matrix to give user hints about the corectly (or partially correctly) guessed letters.  

The game finished when the attempts of the user are exhausted or the correct guess is made.  
*******************************************************************************************************************************/

bool isOpened(string filename, ifstream&input) 
//This function checks if the file is opened successfully and returns true if it is, it returns false otherwise.
{
	input.open(filename.c_str());
	if (input.fail()) 
	{
		cout << "Couldn't find the file!" << endl;
		return false;
	}
	return true;
}

struct cell 
{
	char letter; // letter inside the cell
	char color; // color of the cell
};

vector<vector<cell>> initialize(int allowedAttempts, string trueWord) 
{
/*This function initializes and returns the matrix that will be used in game. It takes the number of attempts as an integer input and sets
the row number of the matrix to the number of attempts. It also takes the correct word to be guessed as a string input to determine
the number of columns of the matrix according to the number of letters in the word. */

	vector<vector<cell>> gamingMatrix(allowedAttempts); //empty matrix with specified number (attempts allowed) of rows

	//initialize the color and letter of cells as "-" and push them to the rows 
	//the number of cell in each row is determined by the number of letters in the true word
	for(int row_number=0; row_number < allowedAttempts; row_number++)
	{
		for(int col_number=0; col_number< trueWord.size(); col_number++)
		{
			cell letters; //struct element that stores color and letter info
			letters.color = '-'; 
			letters.letter = '-'; 
			gamingMatrix[row_number].push_back(letters);
		}
	}
	return gamingMatrix;
}

bool sizeCheck(string guess, string trueWord) 
// This function checks if the guess of the user and the word have the same number of letters, and it prints the appropriate message.
//If the guess and true word have the same length it returns true, it returns false otherwise. 
{
	if(guess.size() < trueWord.size())
	{
		cout << "The word is too short!" << endl;
		return false;
	
	}
	else if(guess.size() > trueWord.size())
	{
		cout << "The word is too long!" << endl;
		return false;
	}
	return true;
}

bool lowercaseLetterCheck(string guess) 
//This function checks if the letters of the guess of the user is all lowercase letters and returns true if so. If not, then it returns false.
{
	for(int idx = 0; idx < guess.size(); idx++) 
	{
		if(isupper(guess[idx]) || !isalpha(guess[idx])) //check if the letter in the specified index is not a lowercase
														//letter or is a non-alphabetical character
		{
			cout << "Your input has illegal letters!" << endl;
			return false;
		}
	}
	return true;
}

bool repeatCheck(string guess) 
//This function checks if the guess of the user has repeated letters and returns false if so. 
//It returns true if the word does not have duplicate letters.
{
	for(int idx = 0; idx < guess.size()-1; idx++) 
	{
		for(int next_idx = idx + 1; next_idx < guess.size(); next_idx++) 
		{
			if(guess[next_idx] == guess[idx]) //compare the two consecutive letters
			{
				cout << "Your input has a duplicate letter!" << endl;
				return false;
			}
		}
	}
	return true;
}

bool triedCheck(string guess, const vector<vector<cell>> & gamingMatrix) 
//This function checks if the guess of the user has been tried previously by comparing the new guess with the old valid guesses.
//It returns false if the guess has been tried, and true otherwise.
{
	for(int row = 0; row < gamingMatrix.size(); row++)
	{
		string word; //to combine letters stored in a row of matrix for getting the entire word 
		for(int col = 0; col < gamingMatrix[0].size(); col++)
		{
			word += gamingMatrix[row][col].letter; //add the letter in the particular cell to the word 
		}
		if (word==guess) //check if the previous guess in the specified row is the same as the current guess
		{
			cout << "You've already tried this word!" << endl;
			return false;
		}
	}
	return true;
}

bool greenCheck(const vector<vector<cell>> gamingMatrix, string guess) 
	//This function checks if the green letters exist at the correct 														
	//position in the current guess of the user. 
{
	for(int row = 0; row < gamingMatrix.size(); row++)
	{
		for(int col = 0; col < gamingMatrix[0].size(); col++)
		{
			if (gamingMatrix[row][col].color == 'G')
			{
				if (guess[col] != gamingMatrix[row][col].letter)
				{
					cout << "You did not use the green letter in your word!" << endl;
					return false;
				}
			}
		}
	}
	return true;
}

bool inputCheck(string guess, string trueWord, const vector<vector<cell>>  & gamingMatrix) 
{
//This function checks the specified conditions for the word that user entered and returns true if the word is valid
//and returns false if one of the constraints is not satisfied with the appropriate message.
	if(sizeCheck(guess, trueWord))
	{
		if(lowercaseLetterCheck(guess))
		{
			if(repeatCheck(guess))
			{
				if(triedCheck(guess, gamingMatrix))
				{
					if(greenCheck(gamingMatrix, guess))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

char colorCheck(string guess, string trueWord, int index) 
//This fuction determines the color code of the letters of the guess that is entered by user 
{
	if(trueWord.find(guess[index]) != string::npos) //check if the letter exists in the true word
	{
		if(trueWord[index] == guess[index]) //check if the guess and the true word have a common letter in the same index
		{
			return 'G'; 
		}
		return 'Y'; //
	}
	return 'B';
}

void printMatrix(vector<vector<cell>> & gamingMatrix)
{
//This fuction prints the 2d matrix that stores the valid guesses made so far.
	for(int row = 0; row < gamingMatrix.size(); row++)
	{
		for(int col = 0; col < gamingMatrix[0].size(); col++)
		{
			cout << "|| " << gamingMatrix[row][col].letter << " , " << gamingMatrix[row][col].color;
		}
		cout << "||" << endl;
	}
}

int main()
{
	string filename; //to store the filename to be opened
	int allowedAttempts; //the allowed attempt number
	string trueWord; //the true word to be guessed
	string guess; //the guess of the user
	ifstream input; //input file stream object to open and read the file

	cout << "Welcome to SWordle!" << endl;

	//take input until the file is opened succesfully
	bool is_open= false; //to check if the file is opened successfully
	while(is_open == false)
	{
		cout << "Please enter the file name: ";
		cin >> filename;
		is_open = isOpened(filename, input);
	}

	input >> allowedAttempts; //read the attempt number from the file
	input >> trueWord; //read the word to be guessed from the file

	input.close(); //close the file that was opened 

	vector<vector<cell>> gamingMatrix = initialize(allowedAttempts, trueWord); //initial matrix that will later store the valid guesses of the user

	cout << "The word that you will guess has " << trueWord.size()  <<  " letters and you have " <<  allowedAttempts << " attempts." << endl;

	int attempt = 0; //number of attempts used so far
	bool is_true = false; //to check if the correct guess is made 
	while((attempt < allowedAttempts) && (is_true != true))
	{
		cout << "What is your guess? ";
		cin >> guess; 

		//take input until the user enters a valid input
		while(inputCheck(guess, trueWord, gamingMatrix) != true)
		{
			cout << "What is your guess? ";
			cin >> guess;
		} 

		//check the colors of the letters of the guess of the user one by one
		for(int index = 0; index < trueWord.length(); index++)
		{
			char color = colorCheck(guess, trueWord, index); //color info of the letter in the specified index
			gamingMatrix[attempt][index].color = color; //set the color info of the letter in the matrix 
			gamingMatrix[attempt][index].letter = guess[index]; //set the letter info of the word in matrix
		}
		
		//print the 2d matrix that stores the valid guesses made so far
		printMatrix(gamingMatrix);

		//check if the guess is true and if so exist the loop by setting is_true to true
		if(guess==trueWord)
		{
			cout << "You win!" << endl;
			is_true = true;
		}
		attempt++; //increase the number of attempts made so far by 1
	}

	//check if the correct guess was not made
	if(!is_true) //is_true becomes true if the correct guess is made but remains false if the correct guess is not made and attempts are finished
	{
		cout << "You lose!" << endl;
	}


	return 0;
}