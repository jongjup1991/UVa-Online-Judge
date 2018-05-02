#include <iostream>
#include <sstream>
#include <string>
#include <cinttypes>
#include <vector>
#include <cstring>
#include <cctype>
#include <set>
#include <cassert>
#include <array>
#include <algorithm>

using namespace std;

#define MAX_IMAGE_LINES_PER_SET 14


// This is the array to be used for holding lines of image data to be processed.
array<string, MAX_IMAGE_LINES_PER_SET> imageLines;

vector<int> totalBlankSpaceCounts;

inline void addXAndDetectTouching (string& imageLine, int addXHere, int& canAddX, int& isTouching) {
	if (canAddX) {
		imageLine[addXHere] = 'X';
	}

	if (imageLine.find(' ') == string::npos) {
		isTouching = 1;
	}
}

// Within a line of image, guaranteed to be 
// 0 or more X's, followed by 0 or more spaces, 
// followed by 0 or more X's, count the number of spaces.
int countBlankSpaces(string s) {
	int j;
	int blankSpacesInS = 0;
	for (j = 0; ((s[j] == 'X') && (j < (s.length()))); j++) {
	}

	int k;
	for (k = j; ((s[k] == ' ') && (k < (s.length()))); k++) {
		blankSpacesInS++;
	}
	return blankSpacesInS;
}

bool hasLessBlankSpace (string a, string b) {
	int blankSpacesInA = countBlankSpaces(a);
	int blankSpacesInB = countBlankSpaces(b);
	return (blankSpacesInA < blankSpacesInB);
}


int main(int argc, char** argv) {
	string imageLine;
	int justStarted = 1;
	int numImageLines = 0;
	while (getline(cin, imageLine)) {

		assert(numImageLines < MAX_IMAGE_LINES_PER_SET);

		// If this is a number, then we are getting told about how many lines of image data follow.
		// While at it, pause to process any previously received image lines.
		if (isdigit(imageLine[0])) {

            // If this is the very first time the loop has been executed,
            // then there are NO previous lines of image data received,
            // so skip for now.
            // It is known that we will never receive a 0 right off the bat
            // (0 indicates that there are no lines of image data that follows)
			if (justStarted) {
				justStarted = 0;
				continue;
			}
            
            // Otherwise, we have more work to do.

            // The "touching" refers to the left and right sides of an image line
            // touching (i.e. all X's with no space in between)
            int isTouching = 0;

            // Sort in ascending order with respect to 
            // the number of blank spaces in each line of image
            sort(imageLines.begin(), imageLines.begin() + numImageLines, hasLessBlankSpace);

            while (isTouching == 0) {
    			int canAddOnLeft= 1;
	            int canAddOnRight = 1;
	            for (int i = 0; i < numImageLines; i++) {
	            	int rightmostLeftX = -1;
	            	int leftmostRightX = -1;

	            	string currentImageLine = imageLines[i];

	            	// First, prepare to perform the surgery (i.e. "bring them toward each other")
	            	// by examining where to add another 'X'
	            	for (int j = 0; j < (currentImageLine.length() - 1); j++) {
	            		if (((currentImageLine[j]) == 'X') && ((currentImageLine[j + 1]) == ' ') && (canAddOnLeft)) {
	            			rightmostLeftX = j;
	            		}
	            		if (((currentImageLine[j]) == ' ') && ((currentImageLine[j + 1]) == 'X') && (canAddOnRight)) {
	            			leftmostRightX = j + 1;
	            		}
	            	}

	            	if ((leftmostRightX == -1) && (rightmostLeftX == -1)) {
	            		isTouching = 1;
	            		break;
	            	}

	            	addXAndDetectTouching(currentImageLine, rightmostLeftX + 1, canAddOnLeft, isTouching);


                    // The i == 0 thing is an important detail for correctness.
                    // Suppose that isTouching becomes 1 after not ONE, but TWO addXAndDetectTouching calls.
                    // Then, at the next iteration when i is 1, what happens without the (i == 0)?
                    // canAddOnLeft becomes 0 when it should not.
	            	if (isTouching && (i == 0)) {
	            		canAddOnLeft = 0;
	            	}

                    // If i is 0, and adding on the left side causes the left-right touch,
                    // this does not change anything.
	            	addXAndDetectTouching(currentImageLine, leftmostRightX - 1, canAddOnRight, isTouching);

	                // Save the changes
	            	imageLines[i] = currentImageLine;

	            }
            }

			

			// Add up ALL of the blank space counts from the received image data.
			int blankSpaceTotal = 0;
			for (int i = 0; i < numImageLines; i++) {
				blankSpaceTotal += countBlankSpaces(imageLines[i]);
			}

			totalBlankSpaceCounts.push_back(blankSpaceTotal);

			// Prepare to reuse the array for next processing.
			numImageLines = 0;


			// If the number received is 0, then we will receive no further image data to process,
			// so exit the main loop now
			if (imageLine[0] == '0') {
				break;
			}

		}

		// Otherwise, this is image data, so add to the previously prepared array for processing.
		else {
			imageLines[numImageLines] = imageLine;
			numImageLines++;
		}
	}

	// Print out the number of total blank spaces for each set of image
	for (vector<int>::iterator i = totalBlankSpaceCounts.begin(); i != totalBlankSpaceCounts.end(); i++) {
		cout << *i << endl;
	}

}

