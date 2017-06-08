// PL homework: hw2
// lr_parser_main.cc

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "lr_parser.h"

#pragma warning (disable: 4996)
using namespace std;

bool LoadLRTable(const char* filename,
                 vector<LRTableElement>* elements, vector<LRRule>* rules) {
	FILE* fp = fopen(filename, "rt");
	if (fp == NULL) 
		return false;

	elements->clear();
	rules->clear();

	int num_elements, num_rules;
	if (fscanf(fp, "%d %d", &num_elements, &num_rules) < 2) 
		return false;

	for (int i = 0; i < num_elements; ++i) {
		LRTableElement elem;
		char action, symbol[64];

		if (fscanf(fp, "%d %s %c %d", &elem.state, symbol, &action, &elem.next_state) < 4) {
			break;
		}

		elem.action = (action == 'S' ? SHIFT : action == 'R' ? REDUCE :
		action == 'G' ? GOTO : action == 'A' ? ACCEPT : INVALID);

		if (elem.action == GOTO) 
			elem.symbol = atoi(symbol);
		else if (elem.action == INVALID) 
			elem.symbol = 0;
		else 
			elem.symbol = symbol[0];

		elements->push_back(elem);
	}

	for (int i = 0; i < num_rules; ++i) {
		LRRule rule;
		if (fscanf(fp, "%d %d %d", &rule.id, &rule.lhs_symbol, &rule.num_rhs) < 3) {
			break;
		}
		rules->push_back(rule);
	}

	fclose(fp);
	return true;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "give the LR table file.\n";
		return -1;
	}

	vector<LRTableElement> elements;
	vector<LRRule> rules;
	LRParser lr_parser;
	string input_str;

	if (LoadLRTable(argv[1], &elements, &rules) == false) {
		cerr << "unable to load the LR table file " << argv[1] << ".\n";
		return -1;
	}

	if (BuildLRParser(elements, rules, &lr_parser) == false) {
		cerr << "unable to build the LR parser (" << argv[1] << ").\n";
		return -1;
	}

	while (!cin.eof()) {
		cout << "> ";
		std::getline(cin, input_str);
		input_str += "$";  // Add EOF symbol.
		bool accept = RunLRParser(lr_parser, input_str);
		cout << "input: '" << input_str << "' = " << (accept? "O" : "X") << endl;
	}
	return 0;
}

