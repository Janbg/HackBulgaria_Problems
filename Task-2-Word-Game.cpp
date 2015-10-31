#include <iostream> 
#include<string>
using namespace std;

// Global variables
const int SIZE_ARRAY = 20;
const int SIZE_WORD = 30;
bool way = false;
short counter = 0;


bool labyrinth(int i, int j, char arr[][SIZE_ARRAY], short n, short m, char word[], short len_word)
{
	if (arr[i][j] != word[0]) {  return false; }

	if (i<0 || i>n-1 || j<0 || j>m-1) { return false; } // If it's out of range

	if (len_word < 1) {  return false; }    // Just in case

	if (word[0] == '\0') { return false; }  // Just in case

	if (len_word == 1 && arr[i][j] == word[0]) // If it finds the word in the array
	{
		way = true; 
		++counter;  // Counter accumulate, how many times it finds the word in the array
	}
	

	if (i >= 0 && i <= n - 1 && j >= 0 && j <= m - 1)
	{
		return  (
			labyrinth(i - 1, j, arr, n, m, word + 1, len_word-1) ||    // Up
			labyrinth(i + 1, j, arr, n, m, word + 1, len_word-1) ||   // Down
			labyrinth(i, j + 1, arr, n, m, word + 1, len_word-1) ||   // Right
			labyrinth(i, j - 1, arr, n, m, word + 1, len_word-1) );   // Left
	}

	return false;  // Just in case 
}

void print_labyrinth(char arr[][SIZE_ARRAY], short n, short m)
{
	for (int i = 0; i < n; ++i)
	{
		cout << endl;
		for (int j = 0; j < m; ++j)
		{
			cout << arr[i][j] << " ";
		}
	}
}

void Example()
{
	char Array[SIZE_ARRAY][SIZE_ARRAY] = {     // N x M
		{ 'i', 'v', 'a', 'n' },
		{ 'e', 'v', 'n', 'h' },
		{ 'i', 'n', 'a', 'v' },
		{ 'm', 'v', 'v', 'n' },
		{ 'q', 'r', 'i', 't' } };

	short n = 5; // Rows
	short m = 4; // Colums

	char word[SIZE_WORD] = "ivan";
	short len_word = strlen(word);

	cout << "\n---> Default Array: \n";
	print_labyrinth(Array, n, m);

	cout << "\n\n---> Default word: " << word << endl;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (Array[i][j] == word[0])
			{
				labyrinth(i, j, Array, n, m, word, len_word);
			}
		}
	}

}

void Submit_your_values()
{
	char Array[SIZE_ARRAY][SIZE_ARRAY] = { '\0' };
	int n;
	int m;

	do
	{
		cout << "\n---> Enter:  (Rows x Columns) = (n x m)  \n";
		cout << "n= "; cin >> n;
		cout << "m= "; cin >> m;
	} while (n < 1 || n > SIZE_ARRAY || n < 1 || n > SIZE_ARRAY);

	cout << "\n---> Enter Array: \n";
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
		cin >> Array[i][j];

	cout << "\n---> You entered: \n";
	print_labyrinth(Array, n, m);

	cout << "\n\n---> Enter the word you find: \n";
	char word[SIZE_WORD] = "\0";
	cout << "word= "; cin >> word;

	short len_word = strlen(word);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (Array[i][j] == word[0])
			{
				labyrinth(i, j, Array, n, m, word, len_word);
			}
		}
	}
}

void Result() 
{
	if (way)
	{
		cout << "\n\n---> Success: the number of words: " << counter << "\n";
	}
	else cout << "\n\n---> NO Results !\n";
}


void Introduction()
{
	cout << "\t\t\t\tWord Game:\n";
	cout << "Enter '1' for use the example\n";
	cout << "\t or\n";
	cout << "Enter '2' for use your values\n";
	short entered;
	do
	{
		cin >> entered;

	} while (entered != 1 && entered != 2);

	if (entered == 1) {
		Example();
	}
	else {
		Submit_your_values();
	}
}

int main()
{

	Introduction();
	  
	Result();

	return 0;
}