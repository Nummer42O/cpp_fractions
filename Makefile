DEFAULT = -g -std=c++17

Main: Fraction test.cpp
	@g++ ${DEFAULT} -c test.cpp -o bin/test.o
	@echo "build $@"
	@c++ ${DEFAULT} bin/fraction.o bin/test.o -o Test
	@echo "linked $@"

Fraction: fraction/fraction.hpp fraction/fraction.cpp
	@g++ ${DEFAULT} -c fraction/fraction.cpp -o bin/fraction.o
	@echo "build $@"