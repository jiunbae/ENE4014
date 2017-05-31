// PL homework: hw2
// regexp_matcher.cc

#include "regexp_matcher.h"

bool BuildRegExpMatcher(const char* regexp, RegExpMatcher* regexp_matcher) {
	vector<Element> elements;
	vector<int> finals;
	int maxStateNum = 1;

	finals = reg_parse(1, string(regexp), maxStateNum, &elements);

	sort(elements.begin(), elements.end(), [](const Element& first, const Element& second) {
		if (first.state == second.state) {
			if (first.str == second.str) {
				return first.next_state < second.next_state;
			} else {
				return first.str < second.str;
			}
		} else {
			return first.state < second.state;
		}
	});

	sort(finals.begin(), finals.end(), [](const int& first, const int& second) {
		return first < second;
	});

	for (auto& element : elements) {
		if (element.str == "#") {
			element.str = "";
		}
	}

	regexp_matcher->fsa = new FiniteStateAutomaton(elements, finals);
	return true;
}

bool RunRegExpMatcher(const RegExpMatcher& regexp_matcher, const char* str) {
	return regexp_matcher.fsa->isAccept(str);
}

vector<int> reg_parse(int init_state, const string& regexp, int& max_state, vector<Element>* elements)
{
	int index = 0;
	int back = regexp.length();
	vector<int> current;
	vector<int> next;
	vector<int> prev;

	current.push_back(init_state);

	while (index < back) {
		for (auto state : current) {

			if (regexp[index] >= 'a' and regexp[index] <= 'z') {
				next.push_back(++max_state);
				elements->push_back(Element(state, max_state, string({ regexp[index] })));
			} else if (regexp[index] == '.') {
				max_state++;
				for (char ch = 'a'; ch <= 'z'; ch++) {
					elements->push_back(Element(state, max_state, string({ ch })));
				}
				next.push_back(max_state);

			} else if (regexp[index] == '|') {
				next = reg_parse(init_state, regexp.substr(index + 1, back - (index + 1)), max_state, elements);
				next.insert(next.end(), current.begin(), current.end());
				index = back;

			} else if (regexp[index] == '[') {
				int bracketStart = index + 1;
				int bracketEnd = index;
				int bracketCount = 0;

				for (;;) {
					if (regexp[bracketEnd] == '[') 
						bracketCount++;
					else if (regexp[bracketEnd] == ']')
						bracketCount--;
					if (bracketCount == 0) 
						break;

					bracketEnd++;

					if (bracketEnd >= back)
						REGEX_ERROR
				}

				max_state++;
				for (int i = bracketStart; i < bracketEnd; ++i) {
					if (regexp[i] >= 'a' && regexp[i] <= 'z') {
						elements->push_back(Element(state, max_state, string({ regexp[i] })));
					} else
						REGEX_ERROR
				}
				next.push_back(max_state);
				index = bracketEnd;

			} else if (regexp[index] == '*') {
				for (auto pState : prev) {
					for (auto cState : current) {
						elements->push_back(Element(cState, pState, "#"));
						elements->push_back(Element(pState, cState, "#"));
					}
				}
				next = current;

			} else if (regexp[index] == '+') {
				for (auto pState : prev) {
					for (auto cState : current) {
						elements->push_back(Element(cState, pState, "#"));
					}
				}
				next = current;

			} else if (regexp[index] == '?') {
				for (auto pState : prev) {
					for (auto cState : current) {
						elements->push_back(Element(pState, cState, "#"));
					}
				}
				next = current;

			} else if (regexp[index] == '(') {
				int bracketStart = index + 1;
				int bracketEnd = index;
				int bracketCount = 0;
				vector<int> temp;

				for(;;) {
					if (regexp[bracketEnd] == '(') 
						bracketCount++;
					else if (regexp[bracketEnd] == ')') 
						bracketCount--;
					if (bracketCount == 0) 
						break;

					bracketEnd++;

					if (bracketEnd >= back)
						REGEX_ERROR
				}

				for (auto cState : current) {
					temp = reg_parse(cState, regexp.substr(bracketStart, bracketEnd - bracketStart), max_state, elements);
					max_state++;

					for (auto tState : temp) {
						elements->push_back(Element(tState, max_state, "#"));
					}
					next.push_back(max_state);
				}
				index = bracketEnd;
			} else {
				REGEX_ERROR
			}
		}

		prev = current;
		current = next;

		next.clear();
		index += 1;
	}

	return current;
}