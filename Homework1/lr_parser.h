// PL homework: hw2
// lr_parser.h

#ifndef _PL_HOMEWORK_LR_PARSER_H_
#define _PL_HOMEWORK_LR_PARSER_H_

#include <string>
#include <vector>
#include <stack>
#include <map>

#ifdef _MSC_VER 
	#define and &&
	#define or ||
	#define not !
#endif

using namespace std;

enum LRAction {
	INVALID = 0,
	SHIFT = 1,
	REDUCE = 2,
	ACCEPT = 3,
	GOTO = 4
};

// The data fields for each type of action:
//   SHIFT : symbol = the input character, next_state = the next state.
//   REDUCE : symbol = lhs of the rule, next_state = the rule id.
//   ACCEPT : none.
//   GOTO : symbol = the state on the stack top, next_state = the next state.

struct LRTableElement {
	int state;
	int symbol;
	LRAction action;
	int next_state;
};

struct LRRule {
	int id;
	int lhs_symbol;
	int num_rhs;
};

struct LRParser {
public:
	LRParser() {}
	LRParser(const vector<LRTableElement>&,
			 const vector<LRRule>&);

	bool run(const string&) const;
private:
	map<int, map<int, LRTableElement > > parse_table;
	map<int, LRRule > rules;
};

bool BuildLRParser(const vector<LRTableElement>&,
                   const vector<LRRule>&,
                   LRParser*);

bool RunLRParser(const LRParser&, const string&);

#endif //_PL_HOMEWORK_LR_PARSER_H_

