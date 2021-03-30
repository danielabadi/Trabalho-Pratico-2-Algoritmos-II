CC=g++
CFLAGS=-Wall -Wextra -g -std=c++11
all : branch back

branch : branch_and_bound.cpp no.cpp
	${CC} ${CFLAGS} branch_and_bound.cpp no.cpp -o ./branch_and_bound

back: backtracking.cpp
	${CC} ${CFLAGS} backtracking.cpp -o ./backtracking