#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iterator>
#include <cassert>

using namespace std;

int* indecesOfSimilarHeights(vector<long long int> sortedLadyHeights, int lowerBound, int upperBound, int numLadyChimpHeights, long long int luchuHeight) {
	int midpoint = (upperBound - lowerBound) / 2;
	int* results = new int[2];

    // The default answer is "no similar heights found"
	results[0] = -1;
	results[1] = -1;

   int isFinished = 0;

	// This is binary search
   do {

      int midpointHeight = sortedLadyHeights[midpoint];
      int shortestHeight = sortedLadyHeights[lowerBound];
      int tallestHeight = sortedLadyHeights[upperBound];
      int belowMidpoint = midpoint - 1;
      int aboveMidpoint = midpoint + 1;

   	if (upperBound - lowerBound < 2) {
   			
         if (shortestHeight == luchuHeight) {
            if (lowerBound != 0) {
               results[0] = lowerBound - 1;
            }
            results[1] = upperBound;
         }

         else if (tallestHeight == luchuHeight) {
            if (upperBound != (sortedLadyHeights.size() - 1)) {
               results[1] = upperBound + 1;
            }
            results[0] = lowerBound;
         }

         // if (shortestHeight > luchuHeight) is true,
         // we are looking at two absolutely shortest lady chimps,
         // and that THE SHORTEST ONE YET
         // is still taller than Luchu
         else if (luchuHeight < shortestHeight) {
            assert (lowerBound == 0);
            results[1] = lowerBound;
          
         }

         // if (tallestHeight < luchuHeight) is true,
         // this means we are actually looking at
         // two absolutely tallest lady chimps,
         // and that THE TALLEST one yet
         // is shorter than Luchu
         else if (tallestHeight < luchuHeight) {
            assert (upperBound == (sortedLadyHeights.size() - 1));
            results[0] = upperBound;
         }

         else {
            assert((shortestHeight < luchuHeight) && (luchuHeight < tallestHeight));
            results[0] = lowerBound;
            results[1] = upperBound;
         }
         isFinished = 1;
   	}
   	
   	else {
   		if (luchuHeight > midpointHeight) {
   			int newLowerBound = midpoint;
   			int newMidpoint = (upperBound - newLowerBound) / 2;
   			newMidpoint += newLowerBound;
   			lowerBound = newLowerBound;
   			midpoint = newMidpoint;
   		}
   	   else  {
   	     	int newUpperBound = midpoint;
   	     	int newMidpoint = (newUpperBound - lowerBound) / 2;
   	      newMidpoint += lowerBound;
   	      upperBound = newUpperBound;
   	      midpoint = newMidpoint;
   	   }
   	}
   } while (isFinished == 0);

   return results;		


}

int main(int argc, char** argv) {
	string line;
	getline(cin, line);
	stringstream lineStream1(line);
	int numLadyChimpHeights;
	lineStream1 >> numLadyChimpHeights;
	vector<long long int> ladyChimpHeights(numLadyChimpHeights);
	getline(cin, line);
	stringstream ladyChimHeightsStream(line);
	for (int i = 0; i < numLadyChimpHeights; i++) {

		// This will always arrive sorted, which is convenient
		// because we will be doing binary search on this later
		ladyChimHeightsStream >> ladyChimpHeights[i];
	}
	int numLuchuHeights;
	getline(cin, line);
	stringstream lineStream2(line);
	lineStream2 >> numLuchuHeights;
	vector<long long int> luchuHeights(numLuchuHeights);
	getline(cin, line);
	stringstream luchuHeightsStream(line);
	for (int i = 0; i < numLuchuHeights; i++) {
		luchuHeightsStream >> luchuHeights[i];
	}

    // Filter out duplicate elements to ensure correctness of binary search.
    // Taking after how sets are defined in math, C++ sets guarantee unique elements
    // and will filter out duplicate elements automatically.
	set<int> ladyChimpHeightsUnique (ladyChimpHeights.begin(), ladyChimpHeights.end());

	ladyChimpHeights.assign(ladyChimpHeightsUnique.begin(), ladyChimpHeightsUnique.end());


	for (int i = 0; i < numLuchuHeights; i++) {
		int* results = indecesOfSimilarHeights(ladyChimpHeights, 0, (ladyChimpHeights.size() - 1), numLadyChimpHeights, luchuHeights[i]);
		int justShorterIndex = results[0];
		int justTallerIndex = results[1];
		if ((justShorterIndex < 0) || (justShorterIndex >= ladyChimpHeights.size())) {
			cout << "X";
		}
		else {
			cout << ladyChimpHeights[justShorterIndex];
		}
		cout << " ";
		if ((justTallerIndex < 0) || (justTallerIndex >= ladyChimpHeights.size())) {
			cout << "X";
		}
		else {
			cout << ladyChimpHeights[justTallerIndex];
		}
		cout << "\n";
		delete[] results;
	}
	return 0;
}