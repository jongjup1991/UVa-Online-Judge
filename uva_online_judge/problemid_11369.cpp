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


int main (int argc, char** argv) {
	int expectedCases = -1;
	string line;
	getline(cin, line);
	stringstream lineStream(line);
	lineStream >> expectedCases;
	vector<int> totalDiscounts;
	for (int i = expectedCases; i > 0; i--) {
		int numItems = 0;
		getline(cin, line);
		stringstream lineStream(line);
		lineStream >> numItems;
		vector<int> items(numItems);

		string itemsString;
		getline (cin, itemsString);

        stringstream itemsStringSstream(itemsString);
		for (int i = 0; i < numItems; i++) {
			itemsStringSstream >> items[i];
		}

		int totalDiscount = 0;

		// No discount for strictly less than 3 items!
		if (numItems >= 3) {
		
            // Note the sorting being in DESCENDING order!
			sort(items.begin(), items.end(), [](int a, int b) {return (a > b);});

            // This is where the "greedy" strategy is used.
			for (int i = 0; i < numItems; i += 3) {
				vector<int> greedyItems;

				// Greedily select 3 of the most expensive items at a time,
				for (int j = i; ((j < (i + 3)) && (j < numItems)); j++) {
					greedyItems.push_back(items[j]);
				}

				// and compute the discount as specified in the problem
				// (i.e. only the cheapest out of the chosen three)
				// Since the original items vector was sorted in descending order,
				// and the most recently added element is at the greatest index,
				// I know that the LAST element in greedyItems is always the cheapest.
				if (greedyItems.size() == 3) {
					totalDiscount += greedyItems[2];
				}
			}
		}

		// Store the result for display later
		totalDiscounts.push_back(totalDiscount);
	}
	for (auto a: totalDiscounts) {
		cout << a << endl;
	}
}