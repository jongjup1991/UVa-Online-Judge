#include <iostream>
#include <sstream>
#include <string>
#include <cinttypes>
#include <vector>
#include <cstring>
#include <cctype>

using namespace std;

int main(int argc ,char** argv) {
	string line;
	while (getline(cin, line)) {
		line.push_back('\n');
		int offset;
		int wordCount = 0;
		int wordRegion = 0;
		for (offset = 0; offset < line.length(); offset++) {
			if (isalpha(line[offset])) {
				wordRegion = 1;
			}
			else {
				if (wordRegion == 1) {
					wordCount++;
				}
				wordRegion = 0;
			}
		}
		cout << wordCount << '\n';
	}
	return 0;
}