CC=g++ -std=c++17 -Wall -Werror -Wextra -pedantic -g
CHECKFLAGS=-lgtest
REPORTDIR=gcov_report
GCOV=--coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open 
	SPECIALFLAGS += -lpthread -lrt -lsubunit -lm
	BREW = .
else
	OPEN_CMD = open
	SPECIALFLAGS += -pthread
	BREW := ${HOME}/homebrew
endif


all: test

s21_matrix_oop.a:
	$(CC) -c s21_matrix.cpp -o matrix_oop.o
	ar rcs s21_matrix_oop.a matrix_oop.o

test: clean
	$(CC) $(GCOV) -c s21_matrix.cpp 
	$(CC) -c tests.cpp $(CHECKFLAGS)
	$(CC) $(GCOV) -o matrix_test tests.o s21_matrix.o $(CHECKFLAGS)
	./matrix_test

clang:
	clang-format -style=Google -i *.cpp
	clang-format -style=Google -i *.h

clang-check:
	clang-format -style=Google -n *.cpp
	clang-format -style=Google -n *.h

leaks: test
ifeq ($(OS), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full ./matrix_test
else
	leaks -atExit -- ./matrix_test
endif

gcov_report: test
	lcov -t "Unit-tests of matrix" -o s21_matrix.info -c -d .
	genhtml -o $(REPORTDIR) s21_matrix.info
	$(OPEN_CMD) ./gcov_report/index.html

lib:
ifeq ($(OS), Linux)
	echo please install gtest
else 
	brew install googletest
endif

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./$(REPORTDIR) *.info ./*.info report matrix_test matrix_oop

.PHONY: s21_matrix_oop.a test clang clang-check leaks gcov_report lib clean