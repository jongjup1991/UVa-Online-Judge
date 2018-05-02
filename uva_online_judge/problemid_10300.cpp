#include <iostream>
#include <sstream>
#include <string>
#include <cinttypes>
#include <vector>

using namespace std;

int main(int argc ,char** argv) {
	string line;
	getline(cin, line);
	stringstream testCasesSStream(line);
	int testCases;
	testCasesSStream >> testCases;
	int* answers = new int[testCases];
	for (int i = 0; i < testCases; i++) {
		getline(cin, line);
		stringstream farmersStream(line);
		int farmers;
		farmersStream >> farmers;
		while (farmers > 0) {
			getline(cin, line);
			stringstream parametersStream(line);
			int landSize;
			parametersStream >> landSize;
			int animals;
			parametersStream >> animals;
			int premiumFactor;
			parametersStream >> premiumFactor;

			// Pedantically speaking, the formula proposed
			// by the problem is:
			// ((land size)/animals * premium factor *  animals)
			// so you see how it really cancels to land size * premium factor.
			answers[i] += (landSize * premiumFactor);
			farmers--;
		}
	}
	for (int j = 0; j < testCases; j++) {
		cout << answers[j] << endl;
	}
	return 0;

}