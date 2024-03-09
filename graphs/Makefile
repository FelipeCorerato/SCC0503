CC = gcc

tests-directory = ./test_cases

clean:
	rm -r src/lib/*/*.o $(program)

compile: ./main.c ./lib/adjacency_matrix.c ./lib/adjacency_matrix.h
	$(CC) -o main ./main.c ./lib/adjacency_matrix.c

exec:
	$(CC) -o main ./main.c ./lib/adjacency_matrix.c
	./main < $(tests-directory)/1.in
	./main < $(tests-directory)/2.in
