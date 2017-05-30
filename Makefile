# Makefile
#

all: fsa lr_parser regexp

clean:
	${RM} *.o fsa lr_parser regexp


fsa: fsa_main.o fsa.o
	${CXX} -o fsa fsa_main.o fsa.o

fsa.o: fsa.cc fsa.h
	${CXX} -c fsa.cc

fsa_main.o: fsa_main.cc fsa.h
	${CXX} -c fsa_main.cc


lr_parser: lr_parser_main.o lr_parser.o
	${CXX} -o lr_parser lr_parser_main.o lr_parser.o

lr_parser.o: lr_parser.cc lr_parser.h
	${CXX} -c lr_parser.cc

lr_parser_main.o: lr_parser_main.cc lr_parser.h
	${CXX} -c lr_parser_main.cc


regexp: regexp_matcher.o regexp_main.o fsa.o
	${CXX} -o regexp regexp_main.o regexp_matcher.o fsa.o

regexp_main.o: regexp_main.cc regexp_matcher.h
	${CXX} -c regexp_main.cc

regexp_matcher.o: regexp_matcher.cc regexp_matcher.h fsa.h
	${CXX} -c regexp_matcher.cc

