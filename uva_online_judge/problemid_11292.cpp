#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iterator>

using namespace std;

void resetThese (vector<int>& yolo, vector<int> & swag) {
	while (yolo.size() > 0) {
		yolo.pop_back();
	}
	while (swag.size() > 0) {
		swag.pop_back();
	}
}

void addHeights(vector<int>& heights, int numHeightValues) {
	while (numHeightValues > 0) {
		int height;
		string line;
		getline(cin, line);
		stringstream lineStream(line);
		lineStream >> height;
		heights.push_back(height);
		numHeightValues--;
	}

}

int main(int argc, char** argv) {
	int numHeads = 0;
	int numKnights = 0;
	vector<int> knightHeights;
	vector<int> headHeights;
	while (1) {
		if (scanf("%d %d", &numHeads, &numKnights) == 2) {
			string removeNewline;
			getline(cin, removeNewline);
			resetThese(knightHeights, headHeights);
			if ((numHeads == 0) && (numKnights == 0)) {
				break;
			}
			else {
				addHeights(headHeights, numHeads);
				addHeights(knightHeights, numKnights);
				sort(knightHeights.begin(), knightHeights.end());
				sort(headHeights.begin(), headHeights.end());
				int headIndex = 0;
				int knightIndex = 0;
				int totalWage = 0;
				bool noKnightCanFight = false;
				while (headIndex < headHeights.size()) {
					while ((knightHeights[knightIndex] < headHeights[headIndex]) && (knightIndex < knightHeights.size())) {
						knightIndex++;
					}
					if (knightIndex >= knightHeights.size()) {
						noKnightCanFight = true;
						break;
					}
					totalWage += knightHeights[knightIndex];
					headIndex++;
					knightIndex++;
				}
				if (noKnightCanFight) {
					cout << "Loowater is doomed!\n";
				}
				else {
					cout << totalWage << "\n";
				}
			}
		}
	}
}