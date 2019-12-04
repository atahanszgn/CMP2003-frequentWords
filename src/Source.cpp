#include <sstream>
#include <ctime>
#include "Fixer.h"

const int alphabet = 27;
int counter[10] = { 0,0,0,0,0,0,0,0,0,0 };
string words[10]{ "","","","","","","","","","" };
int trail = 0;
int temp = 0;
int temp5 = 0;
int temp6 = 0;
bool shift = false;
bool firstins = false;
bool inlist = false;
string stopwords[659];

/*Looking for the words from the constructed array and if array has the word element or the word is http or www or ly return true and break else return false*/
bool sWordControl(string word) {
	for (int i = 0; i < 659; i++) {
		if (stopwords[i] == word || word == "http" || word == "www" || word == "ly") {
			return true;
			break;
		}
	}
	return false;
}

/*Looking for the array and find the minimum and if next element is smaller than minimum return that element and mark it minimum*/
int minLocation(int first, int last, int *arr) {
	int minIndex = first;
	for (int i = first + 1; i <= last; i++) {
		if (arr[i] < arr[minIndex]) {
			minIndex = i;
		}
	}
	return minIndex;
}
/*Swaps two int elements in the array*/
void swapper(int first, int second, int *arr) {
	int b = arr[first];
	arr[first] = arr[second];
	arr[second] = b;

}
/*Swaps two string elements in the array*/
void wordswapper(int first, int second, string *arr) {
	string a = arr[first];
	arr[first] = arr[second];
	arr[second] = a;

}
/*This algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning.*/
void selectionSort(int length, int *arr) {
	int min;
	for (int i = 0; i < length - 1; i++) {
		min = minLocation(i, length - 1, arr);
		swapper(i, min, arr);
		wordswapper(i, min, words);
	}
}

struct TrieNode
{
	TrieNode *children[alphabet];
	int freq;	//Frequency
	bool isEndOfWord;
};

/*Initialize null Trienode*/
TrieNode* newTrieNode()
{
	TrieNode *node = new TrieNode;

	node->isEndOfWord = false;

	for (int i = 0; i < alphabet; i++) {
		node->children[i] = NULL;
	}
	node->freq = 0;
	return node;
}

/*Inserts a key to trienode*/
void insert(TrieNode *oNode, string data)
{
	TrieNode *nNode = oNode;
	int i;
	for (i = 0; i < data.length(); i++)
	{
		int index;
		if (data[i] != '\'') {
			index = data[i] - 'a';
		}
		else {
			index = data[i] - 13;
		}
		if (!nNode->children[index])
			nNode->children[index] = newTrieNode();


		nNode = nNode->children[index];

	}

	nNode->isEndOfWord = true;
	nNode->freq = 1;
	if (firstins == false) {
		words[0] = data;
		counter[0] = nNode->freq;
		firstins = true;

	}
}

/*Looking for given word whether it is in the trienode if it is not present return false*/
bool search(TrieNode *oNode, string data)
{
	TrieNode *nNode = oNode;

	for (int i = 0; i < data.length(); i++)
	{
		int index;
		if (data[i] != '\'') {
			index = data[i] - 'a';
		}
		else {
			index = data[i] - 13;
		}
		if (!nNode->children[index])
			return false;

		nNode = nNode->children[index];
	}

	if (nNode != NULL && nNode->isEndOfWord) {
		nNode->freq++;
		/*Initially trail = 0 if given word's freq >= counter[trail] look up for a word whether it is in the top10 words array if it is initialize temp
		and temp equals to trail - 1 prevent the bug and nonpositive numbers due to first initialize if temp will become -1 set temp 9*/
		if (nNode->freq >= counter[trail]) {
			for (int i = 0; i < 10; i++) {
				if (words[i] == data) {
					temp = trail - 1;
					if (temp < 0) {
						temp = 9;
					}
					trail = i;
					shift = true;

					break;
				}

			}

			if (shift == true) {				//If word already present in top10 words array
				int temp3 = trail + 1;			//Initially next element of found word
				if (temp3 > 9) {
					temp3 = 0;
				}
				/*Looking up for the very next element whether current element's frequency is larger than or equals to or not for sorting*/
				if (counter[temp3] != 0 && nNode->freq >= counter[temp]) {
					while (trail != temp) {
						temp3 = trail + 1;
						if (temp3 > 9) {
							temp3 = 0;
						}
						words[trail] = words[temp3];				//Copies the current element to the back which is smaller than or equals to this element.
						counter[trail] = counter[temp3];
						trail++;									//Move trail to the next element.
						if (trail > 9) {
							trail = 0;
						}
					}

					words[trail] = data;						//Set current elements values in both array.
					counter[trail] = nNode->freq;
				}
				else {
					trail = temp;
				}
				shift = false;
			}
			/*If word is not present while it has lowest frequency set it to the first element of counter array and top10 words array*/
			else {
				counter[trail] = nNode->freq;
				words[trail] = data;
			}

		}
		//Else current element's frequency is smaller than trail element's frequency.
		else {
			temp = trail - 1;
			if (temp < 0) {
				temp = 9;
			}
			for (int i = 0; i < 10; i++) {
				if (words[i] == data) {
					temp5 = i;
					temp6 = i + 1;
					if (temp6 > 9)
						temp6 = 0;
					inlist = true;
					break;
				}
			}
			//While current element's position is not equal to last modified element's position
			while (temp != trail) {
				//temp = trail - 1. Compares the word's freq with the freq at the temp location
				if (nNode->freq >= counter[temp]) // If our word's freq is greater or equal then the freq at the temp location.
				{
					if (inlist == false) //If our word is not in the list
					{
						int temp4 = trail;
						int temp3 = trail + 1;
						if (temp3 > 9)
							temp3 = 0;

						while (temp4 != temp)  //Shifts elements which are after the temp location.
						{
							counter[temp3] = counter[temp4]; // shifts frequency element to the right.
							words[temp3] = words[temp4]; // shifts word element to the right.
							temp3--;
							temp4--;
							if (temp3 < 0)
								temp3 = 9;
							if (temp4 < 0)
								temp4 = 9;

						}
						counter[temp3] = nNode->freq; //Inserts our word's freq to the right of the temp.
						words[temp3] = data; //Inserts our word to the right of the temp. 
						trail++; //We inserted a new word to array so our trail needs to be the next of itself.
						if (trail > 9)
							trail = 0;

					}
					else {
						//temp5 is the modified last element in the top10 array and counter array temp6 is the next element of temp5
						//While we encounter with last modified element again we make copy operations with it to the next element.
						//Until we see the second last modified element in the array.
						while (temp5 != temp) {
							counter[temp5] = counter[temp6];
							words[temp5] = words[temp6];
							temp5++;
							temp6++;
							if (temp5 > 9)
								temp5 = 0;
							if (temp6 > 9)
								temp6 = 0;
						}
						counter[temp5] = nNode->freq;
						words[temp5] = data;
						inlist = false;
					}
					break;

				}
				temp--;
				if (temp < 0) {
					temp = 9;
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}


int main()
{
	int x = 0;
	string stopword;
	string polarity, sayi, date, hak, user, otext; //Fields
	string ftext; //otext : original tweet, ftext: fixed tweet
	string word;
	string Ttemp;

	TrieNode *oNode = newTrieNode();

	ifstream stoptext("stopwords.txt");
	while (stoptext.good()) {
		getline(stoptext, stopword, '\n');
		stopwords[x] = stopword;
		x++;
	}

	cout << "Reading the file. Please wait..." << endl;
	ifstream data("readableFile.csv");


	double timer = clock();
	while (data.good()) {

		getline(data, polarity, ',');
		getline(data, sayi, ',');
		getline(data, date, ',');
		getline(data, hak, ',');
		getline(data, user, ',');
		getline(data, otext, '\n');
		if (Ttemp != otext) {
			ftext = fixer(otext);
			istringstream iss(ftext);

			while (iss >> word) {
				if (sWordControl(word) == false) {
					if (search(oNode, word) == false) {
						insert(oNode, word);
					}
				}
			}
		}
		Ttemp = otext;
	}
	cout << endl;

	selectionSort(10, counter);
	cout << endl;
	cout << "Words\t" << "\t" << "\tOccurences" << endl;
	cout << "----------------------------------" << endl;
	for (int i = 9; i >= 0; i--) {
		cout << words[i] << "\t   ------>   \t" << counter[i] << endl;
	}


	cout << endl;
	cout << "Total Elapsed Time: " << (clock() - timer) / (CLOCKS_PER_SEC) << " seconds.";
	cout << endl;
	system("pause");
	return 0;

}