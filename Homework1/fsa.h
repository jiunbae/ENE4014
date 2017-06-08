// PL homework: hw1
// fsa.h

#ifndef _PL_HOMEWORK_FSA_H_
#define _PL_HOMEWORK_FSA_H_

#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>

#ifdef _MSC_VER 
	#define and &&
	#define or ||
	#define not !
#endif

#define lambda '#'
#define NOT_INIT -1
// Valid characters are alphanumeric and underscore (A-Z,a-z,0-9,_).
// Epsilon moves in NFA are represented by empty strings.

using namespace std;

struct FSATableElement {
	int state = NOT_INIT;
	int next_state = NOT_INIT;
	string str;
public:
	FSATableElement() {}
	FSATableElement(int state, int next, string str) : state(state), next_state(next), str(str) {}
};

using states = set<int>;
using states_input = pair<states, char>;
using container = map<states_input, states>;

struct FiniteStateAutomaton {
private:
	set<char> inputs;
	states init = {};
	states finals = {};
	container element_table;
	vector<FSATableElement> elements;

	// return FSA is NFA
	bool isNFA() const;

	// next state move from given states
	void next_string(const states&);
	// next state move using lambda
	void next_lambda(states&, int) const;

	// build NFA
	bool buildNFA();
	// build DFA
	bool buildDFA();

public:
    FiniteStateAutomaton() {}
    FiniteStateAutomaton(const vector<FSATableElement>&,
						 const vector<int>&);

    bool isAccept(const string&) const;
};


// Run FSA and return true if str is matched by fsa, and false otherwise.
bool RunFSA(const FiniteStateAutomaton& fsa, const string& str);

bool BuildFSA(const vector<FSATableElement>& elements,
              const vector<int>& accept_states,
              FiniteStateAutomaton* fsa);

#endif //_PL_HOMEWORK_FSA_H_
