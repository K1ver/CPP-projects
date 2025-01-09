TARGET = s21_containers.a 
CC = g++ 
CFLAGS = -Wall -Werror -Wextra --std=c++17 
TEST_FLAGS = -lgtest -pthread --coverage -lgtest_main
TEST_TARGET = s21_tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
OS = open
UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	OS = xdg-open
endif

all: test 
 
clean: 
	@rm -rf *.o *.a gcov_report/ $(TEST_TARGET) *.info *.gcda *.gcno 
 
test: clean 
	$(CC) $(CFLAGS) Tests/s21*.cpp $(TEST_FLAGS) -o $(TEST_TARGET) 
	@$(VALGRIND) ./$(TEST_TARGET) 
	@lcov --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch --capture --directory . --output-file coverage.info 
	@lcov --remove coverage.info '/usr/*' -o coverage.info 
	@genhtml coverage.info --output-directory gcov_report
	@$(OS) gcov_report/index.html

style: 
	@find . -type f \( -name "*.h" -o -name "*.hpp" -o -name "*.tpp" -o -name "*.cpp" \) -exec clang-format -i {} \;
	@find . -type f \( -name "*.h" -o -name "*.hpp" -o -name "*.tpp" -o -name "*.cpp" \) -exec clang-format -n {} \; 

.PHONY: all clean test style
