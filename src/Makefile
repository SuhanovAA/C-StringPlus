FLAGS=-Wall -Werror -Wextra -std=c11
CC=gcc $(FLAGS)
FILE=s21_string
FILETEST=./tests/*.c
FILEREPORT=s21_test_report
FILETESTO=s21_test
DIRREPORT=report
LIB=$(FILE).a
COVFLAG=-fprofile-arcs -ftest-coverage

OS = $(shell uname)

ifeq ($(OS), Linux)
	TESTFLAGS=-pthread -lcheck_pic -lrt -lm -lsubunit
	OPEN_CMD=xdg-open
else
	TESTFLAGS=-pthread -lm -lcheck
	OPEN_CMD=open
endif

all: clean $(FILE).a test gcov_report

o_files:
	$(CC) -c *.c

$(FILE).a: o_files
	ar rcs $(LIB) *.o

test: $(FILE).a
	$(CC)  $(FILETEST) $(FILE).a -o $(FILETESTO) $(TESTFLAGS)
	./$(FILETESTO)

gcov_report: $(FILE).a
	$(CC) $(COVFLAG) $(FILETEST) *.c -o $(FILEREPORT) $(TESTFLAGS)
	./$(FILEREPORT)
	lcov -t "$(FILE)" -o $(FILETEST).info -c -d .  
	genhtml -o $(DIRREPORT) $(FILETEST).info
	$(OPEN_CMD) $(DIRREPORT)/index.html

rep: gcov_report

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info tests/*.info $(DIRREPORT) $(FILETESTO) $(FILEREPORT)

#style
cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h tests/*.c

clang:
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -n *.c *.h tests/*.c
	clang-format -i *.c *.h tests/*.c
	rm -rf .clang-format

check: cpp clang