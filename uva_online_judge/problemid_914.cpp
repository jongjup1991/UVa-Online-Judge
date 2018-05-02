#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iterator>

#define MAX_NUMBERS 1000001

using namespace std;

int currentLowerBound = -1;
int currentUpperBound = -1;

bool smallerThanLower(int i) {
	if (i < currentLowerBound) {
		return true;
	}
	return false;
}

bool greaterThanUpper(int i) {
	if (i > currentUpperBound) {
		return true;
	}
	return false;
}


/*
Picture a vector laid out as [2, 3, 4, 5, ...], so that index 0 is 2, index 1 is 3, etc.
Multiples of 2 can be found at indeces 0, 2, 4, 6...
Multiples of 3 can be found at indeces 1, 4, 7, 10...
Multiples of 5 can be found at indeces 3, 8, 13, 18...
Multiples of 7 can be found at indeces 5, 12, 19, 26...
If beforeSieve[index] == prime, then its multiples, excluding itself,
can be found at indeces 2 * beforeSieve[index] - 2, at increments of beforeSieve[index].
*/    
void sieveOfEdog(vector<int>& beforeSieve, vector<int>& afterSieve) {
	for (int i = 0; i < beforeSieve.size(); i++) {
		if ((beforeSieve[i] != -1) || (beforeSieve[i] > 1)) {
			for (int j = (2 * beforeSieve[i]) - 2; j < beforeSieve.size(); j += beforeSieve[i]) {
				beforeSieve[j] = -1;
			}
		}
	}
	for (int k = 0; k < beforeSieve.size(); k++) {
		if (beforeSieve[k] != -1) {
			afterSieve.push_back(beforeSieve[k]);
		}
	}
}


// The "jumping champion" criteron requires that the differences
// between the consecutive prime numbers be recorded, so...
int recordDifferences(vector<int> primes, vector<int>& recordHere) {
	int i = 0;
	int recordIndex = 0;
	int k;
	while (i < (primes.size() - 1)) {
		if (primes[i] == -1) {
			i++;
			continue;
		}
		int j = i + 1;
		while ((primes[j] == -1) && (j < (primes.size() - 1))) {
			j++;
		}
		if ((j == (primes.size() - 1)) && (primes[j] == -1)) {
			break;
		}
		recordHere[recordIndex] = (primes[j] - primes[i]);
		i = j; 
	    recordIndex++;
	}
	return recordIndex;
}


int main(int argc, char** argv) {
	int numLines;
	cin >> numLines;
	while (numLines > 0) {
		vector<int> differences(MAX_NUMBERS);
		vector<int> candidates(MAX_NUMBERS);
		vector<int> sievedCandidates;
		for (int i = 0; i < MAX_NUMBERS; i++) {
			candidates[i] = i;
		}
		candidates.erase(candidates.begin());
		candidates.erase(candidates.begin());
		sieveOfEdog (candidates, sievedCandidates);
		int lowerBound;
		int upperBound;
		cin >> lowerBound >> upperBound;
		if ((upperBound - lowerBound) == 0)  {
			cout << "No jumping champion\n";
			numLines--;
			continue;
		}
		else if (((lowerBound) < 2 ) && (upperBound < 2)) {
			cout << "No jumping champion\n";
			numLines--;
			continue;
		}
		currentLowerBound = lowerBound;
		currentUpperBound = upperBound;
		int numSieveCandidates = upperBound - lowerBound + 1;
		if (lowerBound > 1) {
			sievedCandidates.erase(remove_if(sievedCandidates.begin(), sievedCandidates.end(), smallerThanLower), sievedCandidates.end());
		}
		sievedCandidates.erase(remove_if(sievedCandidates.begin(), sievedCandidates.end(), greaterThanUpper), sievedCandidates.end());
/*
		for (int i = 0; i < sievedCandidates.size(); i++) {
			cout << sievedCandidates[i] << " ";
		}

		cout << endl;
*/
		if (sievedCandidates.size() < 2) {
			cout << "No jumping champion\n";
			numLines--;
			continue;
		}
		else if (sievedCandidates.size() == 2) {
			printf("The jumping champion is %d\n", sievedCandidates[1] - sievedCandidates[0]);
			numLines--;
			continue;
		}
		int winner = -1;
		int actualDifferencesSize = recordDifferences(sievedCandidates, differences);
/*
		for (int i = 0; i < actualDifferencesSize; i++) {
			cout << differences[i] << " ";
		}
		cout << endl;
*/
		sort(differences.begin(), differences.begin() + actualDifferencesSize);

		vector<int> uniqueDifferences;
		for (int i = 0; i < actualDifferencesSize; i++) {
			uniqueDifferences.push_back(differences[i]);
		}
		set<int> removeDuplicates(uniqueDifferences.begin(), uniqueDifferences.end());

		uniqueDifferences.assign(removeDuplicates.begin(), removeDuplicates.end());

		map<int, int> tallies;

		for (int i = 0; i < uniqueDifferences.size(); i++) {
			tallies.insert(pair<int, int>(uniqueDifferences[i], 0));
		}

		for (int i = 0; i < actualDifferencesSize; i++) {
			if (binary_search(uniqueDifferences.begin(), uniqueDifferences.end(), differences[i])) {
				tallies[differences[i]] += 1;
			}
		}


/*
		for (int i = 0; i < uniqueDifferences.size(); i++) {
			cout << "Tally for " << uniqueDifferences[i] << ": " << tallies[uniqueDifferences[i]] << endl;
		}
*/
		int highestTally = 1;
		for (int i = 0; i < uniqueDifferences.size(); i++) {
			if (tallies[uniqueDifferences[i]] > highestTally) {
				winner = uniqueDifferences[i];
				highestTally = tallies[uniqueDifferences[i]];
			}
		}

		for (int i = 0; i < uniqueDifferences.size(); i++) {
			if (highestTally == tallies[uniqueDifferences[i]]) {
				if (winner != uniqueDifferences[i]) {
					winner = -1;
					break;
				}
			}
		}


		if (winner == -1) {
			cout << "No jumping champion\n";
		}
		else {
			printf("The jumping champion is %d\n", winner);
		}

		numLines--;
	}
	return 0;
}