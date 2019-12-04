#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
Fixer function look up the word and if word has non-letter symbol, deletes and make it simple word.
And if words are seperated by comma or point or slash, replaces that symbol with space and make the words are seperated by namespace.
*/

string fixer(string word) {

	bool match = false;

	for (int i = 0; i < word.length(); i++) {
		match = false;
		if ((word[i] >= 97 && word[i] <= 122) || (word[i] >= 65 && word[i] <= 90))
		{
			match = true;
		}
		else if (word[i] == ' ') {
			match = true;
		}
		else if ((i > 0 && i < word.length() - 1) && ((word[i + 1] >= 97 && word[i + 1] <= 122) || (word[i + 1] >= 65 && word[i + 1] <= 90))
			&& ((word[i - 1] >= 97 && word[i - 1] <= 122) || (word[i - 1] >= 65 && word[i - 1] <= 90)) && word[i] == '\'')
		{
			match = true;
		}

		else if ((word[i] == ',' || word[i] == '.' || word[i] == '/' || word[i] == ':') && (word[i + 1] >= 97 && word[i + 1] <= 122) || (word[i + 1] >= 65 && word[i + 1] <= 90)) {
			word[i] = ' ';
			match = true;
		}


		if (match == false) {
			word.erase(word.begin() + i);
			i--;
		}
	}


	for (int i = 0; i < word.length(); i++) {						//This for loop function converts uppercase letters to lowercase letters to prevent
																// two different words that will result from misspelling.
		if ((word[i] >= 65 && word[i] <= 90))								// For example woRD and word are two different words according to compiler.
		{															//With this letter swap both will be same word.
			word[i] += 32;
		}

	}

	return word;
}