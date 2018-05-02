#include <iostream>
#include <sstream>
#include <string>
#include <cinttypes>
#include <vector>
#include <cstring>
#include <cctype>

using namespace std;

int computeHamming(int num, int maxBits) {
	int hammingDistance = 0;
	for (int i = 0; i < maxBits; i++) {
		if (((num >> i) & 1) == 1) {
			hammingDistance++;
		} 
	}
	return hammingDistance;
}

int main(int argc, char** argv) {
	string line;

	vector<vector<int>*> allHammingCodes(0);
	int numDataSets = -1;
	int passedFirstDataSet = 0;
	while (getline(cin, line)) {
		stringstream lineStream(line);

		if (line.size() == 0) {
			numDataSets--;
			if (passedFirstDataSet == 1) {
				if (numDataSets == -1) {
					break;
				}
			}
			if ((passedFirstDataSet == 1) && (numDataSets == -1)) {
				break;
			}
		}

		else if (line.size() == 1) {
			lineStream >> numDataSets;
		}
		else if (line.size() > 1) {
			passedFirstDataSet = 1;
			int numBits;
			int matchThisHammingDistance;
			stringstream lineStream(line);
			lineStream >> numBits;
			lineStream >> matchThisHammingDistance;
			vector<int>* hammingCodesForThisDataset = new vector<int>();
			hammingCodesForThisDataset->push_back(numBits);
			int largestPossible = (1 << numBits);
			for (int i = 0; i < largestPossible; i++) {
				if (computeHamming(i, numBits) == matchThisHammingDistance) {
					hammingCodesForThisDataset->push_back(i);
				}
			}
			allHammingCodes.push_back(hammingCodesForThisDataset);
		}
	}

	for (int i = 0; i < allHammingCodes.size(); i++) {
		int numBits = -1;
		for (int j = 0; j < allHammingCodes[i]->size(); j++) {
			if (j == 0) {
				numBits = allHammingCodes[i]->at(j);
			}
			else {
				for (int k = (numBits - 1); k >= 0; k--) {
					cout << ((allHammingCodes[i]->at(j) >> k) & 1);
				}
				cout << '\n';
			}
		}
		if (i < (allHammingCodes.size() - 1)) {
			cout << '\n';
		}
	}

	return 0;
}