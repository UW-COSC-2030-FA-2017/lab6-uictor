// SortedDriver.cpp
// Victor Anthony
// 10/29/2017

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that 
//   process the sorted sequences.


#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"


using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t x = 0; x < listSize; ++x)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));
	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t x = 0; x < numWords; ++x)
	{
		string word;
		for (size_t y = 0; y < wordLength; ++y)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();
	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{

	double distance;
	double isolated;
	double totalDist;
	double first;
	double second;

	isolated = number[0];
	distance = abs(number[1] - number[0]);
	totalDist = distance;

	for (int x = 1; x < (number.size() - 1); x++) {
		first = abs(number[x] - number[x - 1]);
		second = abs(number[x + 1] - number[x]);

		if (second > first) {
			if (first > distance) {
				distance = first;
				isolated = number[x];
				totalDist = first + second;
			}
			if (first == distance && (x - 1) == 0) {
				isolated = x;
			}
			if (first == distance) {
				double iDistance = first + second;
				if (iDistance > totalDist) {
					distance = first;
					isolated = number[x];
					totalDist = iDistance;
				}
			}
		}
		if (first > second) {
			if (second > distance) {
				distance = second;
				isolated = number[x];
				totalDist = first + second;
			}
			if (second == distance) {
				double iDistance = first + second;
				if (iDistance > totalDist) {
					distance = second;
					isolated = number[x];
					totalDist = iDistance;
				}
			}
		}
	}

	first = abs(number[number.size() - 1] - number[number.size() - 2]);
	if (first > distance) {
		distance = first;
		isolated = number[number.size() - 1];
	}
	return isolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int unmatched(list<string> & A, list<string> & B)
{
	int counter = 0;
	list<string>::iterator x = A.begin();
	list<string>::iterator y = B.begin();

	while (y != B.end() && x != A.end()) {
		if (*x == *y) {
			x++;
		}
		else if (*x > *y) {
			y++;
		}
		else if (*x < *y) {
			counter++;
			x++;
		}
	}
	return counter;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;

	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}
	return 0;
}
