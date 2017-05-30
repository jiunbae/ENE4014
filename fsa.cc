// PL homework: hw1
// fsa.cc

#include <iostream>

#include "fsa.h"

#define DISABLE_LOG true
#define LOG \
    if (DISABLE_LOG) {} else std::cerr

using namespace std;

bool RunFSA(const FiniteStateAutomaton& fsa, const string& str) {
    return fsa.isAccept(str);
}

bool BuildFSA(const std::vector<FSATableElement>& elements,
              const std::vector<int>& accept_states,
              FiniteStateAutomaton* fsa) {

    *fsa = FiniteStateAutomaton(elements, accept_states);

    LOG << "num_elements: " << elements.size()
        << ", accept_states: " << accept_states.size() << endl;
	return true;
}

FiniteStateAutomaton::FiniteStateAutomaton(const vector<FSATableElement>& elements,
										   const vector<int>& accept_states) {

	this->elements = elements;

	for (auto state : accept_states) {
		finals.insert(state);
	}

	init.insert(this->elements[0].state);

	if (isNFA()) {
		buildNFA();
	} else {
		buildDFA();
	}
}

bool FiniteStateAutomaton::isNFA() const
{
	FSATableElement pElements;

	for (auto element : elements) {
		if (element.str.empty()) {
			return true;
		}
		for (auto ch : element.str) {
			if (pElements.state != NOT_INIT) {
				if (pElements.state == element.state &&
					pElements.str[0] == ch) {
					return true;
				}
			}
			pElements = element;
			pElements.str[0] = ch;
		}
	}
	return false;
}

void FiniteStateAutomaton::next_string(const states& from)
{
	states next;

	for (auto input : inputs) {
		next.clear();

		for (auto state : from) {
			for (auto element : elements) {
				for (auto ch : element.str) {
					if (element.state == state and ch == input) {
						next.insert(element.next_state);

						int j;
						for (j = 0; j < elements.size(); j++) {
							if (elements[j].state == element.next_state) {
								break;
							}
						}
						next_lambda(next, j);
					}
				}
			}
		}

		states_input current(from, input);

		if (element_table.find(current) == element_table.end() and not next.empty()) {
			element_table[current] = next;
			next_string(next);
		}
	}
}

void FiniteStateAutomaton::next_lambda(states& from, int start) const
{
	if (start >= elements.size()) return;
	int current = elements[start].state;
	auto begin = elements.begin();
	auto end = elements.end();

	for (auto element : vector<FSATableElement>(begin + start, end)) {
		if (not element.str.empty() or element.state != current)
			break;

		from.insert(element.next_state);

		int j;
		for (j = 0; j < elements.size(); j++) {
			if (elements[j].state == element.next_state) {
				break;
			}
		}

		if (elements[j].str.empty()) {
			if (from.find(j) != from.end()) {
				next_lambda(from, j);
			}
		}
	}
}

bool FiniteStateAutomaton::buildNFA()
{
	for (auto element : elements) {
		for (auto ch : element.str) {
			inputs.insert(ch);
		}
	}
	states current({ init });
	next_lambda(current, 0);
	init = current;
	next_string(current);
	
	return true;
}

bool FiniteStateAutomaton::buildDFA()
{
	for (auto element : elements) {
		for (auto ch : element.str) {
			states_input current(states({ element.state }), ch);

			if (element_table.find(current) != element_table.end()) {
				element_table[current].insert(element.next_state);
			} else {
				element_table[current] = states({ element.next_state });
			}
		}
	}
	return true;
}

bool FiniteStateAutomaton::isAccept(const string& str) const {
    
	states current = init;

	for (auto ch : str) {
		states_input input(current, ch);

		auto target = element_table.find(input);
		if (target != element_table.end()) {
			current = element_table.at(input);
		} else {
			return false;
		}
	}

	for (auto state : current) {
		for (auto element : elements) {
			if (element.state == state and element.str.empty()) {
				current.insert(element.next_state);
			}
		}
	}

	for (auto state : current) {
		if (finals.find(state) != finals.end()) {
			return true;
		}
	}

    return false;
}
