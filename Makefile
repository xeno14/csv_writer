example: example.cpp csv_writer.h
	g++ $< -std=c++11 -Wall -o $@

test: test.cpp csv_writer.h
	g++ $< -std=c++11 -Wall -o $@
