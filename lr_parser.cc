// PL homework: hw2
// lr_parser.cc

#include <assert.h>

#include <iostream>

#include "lr_parser.h"

#define DISABLE_LOG false
#define LOG \
    if (DISABLE_LOG) {} else std::cerr

bool BuildLRParser(const vector<LRTableElement>& elements,
                   const vector<LRRule>& rules,
                   LRParser* lr_parser) {

	*lr_parser = LRParser(elements, rules);

	return true;
}

bool RunLRParser(const LRParser& lr_parser, const string& str) {
	return lr_parser.run(str);
}

LRParser::LRParser(const vector<LRTableElement>& elements, const vector<LRRule>& rules) {
	for (auto element : elements) {
		this->parse_table[element.state][element.symbol] = element;
	}

	for (auto rule : rules) {
		this->rules[rule.id] = rule;
	}
}

bool LRParser::run(const string & str) const {
	int str_index = 0;
	int stack_index = 0;
	vector<int> stack({ 0 });

	int reducedFactor;
	bool isReduced = false;

	for (;;) {
		int nextInput = str[str_index];

		if (isReduced) {
			isReduced = false;
			nextInput = reducedFactor;
		}

		auto it = parse_table.find(stack[stack_index])->second.find(nextInput);

		if (it != parse_table.find(stack[stack_index])->second.end()) {
			int ruleNum, numToPop;
			switch (it->second.action) {
				case SHIFT:
					stack.push_back(nextInput);
					stack.push_back(it->second.next_state);

					stack_index += 2;
					str_index++;
					break;

				case REDUCE:
					ruleNum = it->second.next_state;
					numToPop = rules.find(ruleNum)->second.num_rhs;

					for (int i = 0; i<numToPop * 2; i++) {
						stack.pop_back();
					}

					stack_index -= numToPop * 2;

					reducedFactor = rules.find(ruleNum)->second.lhs_symbol;
					isReduced = true;
					break;

				case GOTO:
					stack.push_back(nextInput);
					stack.push_back(it->second.next_state);

					stack_index += 2;
					break;

				case ACCEPT:
					return true;

				default:
					return false;
			}
		} else {
			return false;
		}
	}
}
