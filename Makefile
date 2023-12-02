CXX = gcc
SRC = timer.c

build:
	$(CXX) $(SRC) -o timer

run: build
	./timer -h 1 

run_hms : build
	./timer -h 1 -m 1 -s 1

run_hm : build
	./timer -h 1 -m 1

run_ms : build
	./timer -m 1 -s 1

run_h : build
	./timer -h 1

run_bin : build
	sudo cp timer /usr/local/bin