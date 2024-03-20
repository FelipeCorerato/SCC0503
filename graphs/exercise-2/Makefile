CC = gcc

tests-directory = ./test_cases

clean:
	rm -r lib/*/*.o $(program)

all: ./main.c lib/adjacency_matrix/adjacency_matrix.c lib/adjacency_matrix/adjacency_matrix.h lib/queue/queue.c lib/queue/queue.h
	$(CC) -o main ./main.c ./lib/adjacency_matrix/adjacency_matrix.c ./lib/queue/queue.c

run:
	$(CC) -o main ./main.c ./lib/adjacency_matrix/adjacency_matrix.c ./lib/queue/queue.c
	./main

test:
	$(CC) -o main ./main.c ./lib/adjacency_matrix/adjacency_matrix.c ./lib/queue/queue.c
	@for input_file in $(tests-directory)/*.in; do \
		base_name=$$(basename $$input_file .in); \
		output_file=$(tests-directory)/$$base_name.out; \
		echo "\nExecuting test case: $$base_name"; \
		./main < $$input_file > output_temp.out; \
		diff_output=$$(diff -ub output_temp.out $$output_file); \
		if [ -z "$$diff_output" ]; then \
			echo "	✅ Test succeed!"; \
		else \
			echo "	❌ Test failed!"; \
			echo "$$diff_output"; \
		fi; \
		rm output_temp.out; \
	done

generate-single-file:
	@ > single-main.c
	@ find ./lib -type f -name '*.h' -exec cat {} + >> single-main.c
	@ echo "" >> single-main.c
	@ find ./lib -type f -name '*.c' -exec cat {} + >> single-main.c
	@ echo "" >> single-main.c
	@ cat main.c >> single-main.c
	@ echo "Remember to remove the unused imports!"
