CC=g++ -std=c++17 -O -lgmp -lgmpxx -lm -Wfatal-errors
MAKEFLAGS += --no-builtin-rules

./%.run: ./%.cpp ./utils
	$(CC) -o $@ ./$(basename $@).cpp ./utils/*.o -Iutils/

.PHONY: utils
utils: ./utils/gmp_util.o ./utils/number_util.o ./utils/prime_util.o ./utils/io_util.o ./utils/string_util.o ./utils/pell_util.o

./utils/%.o: ./utils/%.cpp
	$(CC) -c -o $@ $(basename $@).cpp

.PHONY: clean
clean:
	rm -f utils/*.o
	rm -f ./*.run
