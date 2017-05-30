// PL homework: hw2
// regexp_main.cc

#include <stdio.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "regexp_matcher.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "give the regexp pattern.\n";
		return -1;
	}

	RegExpMatcher regexp;
	if (BuildRegExpMatcher(argv[1], &regexp) == false) {
		cerr << "unable to build the matcher from regexp '" << argv[1] << "'.\n";
		return -1;
	}

	string input_str;
	while (!cin.eof()) {
		cout << "> ";
		std::getline(cin, input_str);
		bool accept = RunRegExpMatcher(regexp, input_str.c_str());
		cout << "input: '" << input_str << "' = " << (accept? "O" : "X") << endl;
	}
	return 0;
}
