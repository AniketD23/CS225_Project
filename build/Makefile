CXX_FLAGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra
CXX = clang++

exec: bin/exec
tests: bin/tests

main: ../code/main.cpp ../code/data_processing.cpp ../code/data_processing.h
	${CXX} ${CXX_FLAGS} ../code/main.cpp ../code/data_processing.cpp -o main
