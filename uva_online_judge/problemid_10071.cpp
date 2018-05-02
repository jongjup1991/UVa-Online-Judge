#include <iostream>
#include <sstream>
#include <string>
#include <cinttypes>
#include <vector>

using namespace std;

int main(int argc ,char** argv) {
	vector<string> inputs(0);
	string line;
	getline(cin, line);
	while (line.length() != 0) {
		inputs.push_back(line);
		getline(cin, line);
	}
	for (int i = 0; i < inputs.size(); i++) {
		stringstream lineStream(inputs[i]);
		int64_t v;
		lineStream >> v;
		int64_t t;
		lineStream >> t;
		cout << v * 2 * t << endl;
	}
	return 0;
}