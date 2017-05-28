# Programming Languages Homeworkd 1

Write C/C++ functions that builds and runs a FSA and an LR parser, and runs regular expressions.

- Skeleton codes are provided with the assignment.
- DO NOT change the `fsa_main.cc` , `lr_parser_main.cc` , and `regexp_main.cc` files.

1.1 Write a C/C++ function that builds a DFA from a finite state automaton definition. [50pts]

- The input file structure is the accept states at the first line, followed by (`state, next_state, input_char`) triplets. The `epsilon` move is marked as `#` in the text file.
```
3 4
1 3 #
1 2 a
2 2 bc
2 4 b
3 2 #
3 4 a
4 3 ac
```
- Implement the `RunFSA` and `BuildFSA` functions so that it can process both DFA and NFA definitions

1.2 Write C/C++ functions : a function that loads an LR parsing table to build an LR parser, and a function that runs it on input token strings and returns the acceptance (true/false). [50pts]

- The LR parser table file structure is as follows
```
num_table_elements num_rules
state symbol action next_state
...
rule_id lhs_symbol num_rhs
...
```
- Refer description in the header file `lr_parser.h` for more details.
- Design the LRParser structure in `lr_parser.h`.
- Implement the `BuildLRParser` function that builds `LRParser` structure using the given table elements.
- Implement the `RunLRParser` function so that it returns the acceptance of the given token string.

1.3 Write a C/C++ function that builds DFA from a regular expression string. [50pts]

- Design and implement the parser that builds NFA from the regular expression, consisting of single characters `abc`, any character `.`, set of characters `[abc]`, OR `a|b`, zeroormore repetition (`a*`), and group (`abc`).
```
ab|cd : ab, cd
a(b|c)d : abd, acd
a.*b : ab, acb, axyzb, ...
(a(b.c)*|de)f : af, def, abxcf, abxcbycf, ...
[abc]*def : adef, bdef, cdef, aadef, abdef, ...
```
- Convert the built NFA into DFA and match the input string with the regular expression.


**Due : May 31 (Wed) 11:59 pm**

– Zip the source code (ONLY .h, .cc and Makefile; absolutely no executable or object files) and submit it in ezhub (portal).
– The program must run on the Linux server (csedev.hanyang.ac.kr).