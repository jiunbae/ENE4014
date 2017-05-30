// PL homework: hw2
// regexp_matcher.h

#ifndef _PL_HOMEWORK_REGEXP_MATCHER_H_
#define _PL_HOMEWORK_REGEXP_MATCHER_H_

#include <vector>
#include <algorithm>
#include <string.h>
#include "fsa.h"

#ifdef _MSC_VER 
	#define and &&
	#define or ||
	#define not !
#endif

#define lambda '#'
#define in :
#define NOT_INIT -1

#define REGEX_ERROR exit(1);

using namespace std;

using Element = FSATableElement;

struct RegExpMatcher {
	FiniteStateAutomaton * fsa;
};

bool BuildRegExpMatcher(const char*, RegExpMatcher*);

bool RunRegExpMatcher(const RegExpMatcher&, const char*);

vector<int> reg_parse(int initialState, const string& regexp, int& maxStateNum, vector<Element>* fsa_elements);

#endif  //_PL_HOMEWORK_REGEXP_MATCHER_H_

