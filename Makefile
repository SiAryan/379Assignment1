all: shell379 test

clean:
	@rm -rf shell379 test		

test: test.cpp
	g++ -std=c++11 test.cpp -o test

shell379: shell379.cpp commands.cpp commands.h
	g++ -std=c++11 shell379.cpp commands.cpp commands.h -o shell379	 	