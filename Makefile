CC = gcc -Wall -Werror -Wextra
GCOV=-fprofile-arcs -ftest-coverage
REPORTDIR = gcovdir
FILE_LIB = matrix
FILE = test

OS = $(shell uname)
ifeq ($(OS), Darwin)
  CHECKFLAGS=-lcheck
else
  CHECKFLAGS=-lcheck -lpthread -lrt -lm -lsubunit
endif

all: clean $(FILE_LIB).a

$(FILE_LIB).a: $(FILE_LIB).c
	$(CC) -c $(FILE_LIB).c -o $(FILE_LIB).o 
	ar rcs $(FILE_LIB).a $(FILE_LIB).o

test: clean $(FILE_LIB).a
	$(CC) -c $(FILE).c -o $(FILE).o 
	$(CC) $(FILE).o $(FILE_LIB).o $(CHECKFLAGS) -o $(FILE)

	./$(FILE)

gcov_report: $(FILE_LIB).a
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.info $(REPORTDIR)
	$(CC) $(GCOV) $(FILE).c $(CHECKFLAGS) $(FILE_LIB).c -o $(FILE_LIB)

	./$(FILE_LIB)
	lcov -t "Unit-tests of $(FILE_LIB)" -o $(FILE_LIB).info -c -d .
	genhtml -o $(REPORTDIR) $(FILE_LIB).info

clean:
	rm -rf *.dSYM *.o *.a *.out *.gcno *.gcda *.gcov *.info $(REPORTDIR) $(FILE) $(FILE_LIB)