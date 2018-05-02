#include <iostream>
#include <sstream>
#include <string>
#include <cinttypes>
#include <vector>

using namespace std;

int main(int argc ,char** argv) {
	string line;
	getline(cin, line);
	while (line.length() != 0) {
		for (int i = 0; i < line.length(); i++) {

			// The trick behind the "encryption" in the problem
			// is merely a matter of ASCII arithmetic.
			cout << char(line[i] - 7);
		}
		cout << endl;
		getline(cin, line);
	}
}