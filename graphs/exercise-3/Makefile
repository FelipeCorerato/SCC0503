TARGET = programa

CXX = g++

CXXFLAGS = -Wall -std=c++11 -Ilib/graph/

# Encontrar todos os arquivos .cpp no diretório atual e no diretório lib/graph/
SOURCES = $(wildcard *.cpp) $(wildcard lib/graph/*.cpp)

# Gerar nomes de arquivos .o no diretório atual, não importa onde os .cpp estejam
OBJECTS = $(notdir $(SOURCES:.cpp=.o))

all: $(TARGET)

# Como construir o executável final
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Como construir os objetos .o a partir dos .cpp
# Note a mudança aqui para lidar com a compilação de arquivos em subdiretórios
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
%.o: lib/graph/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

# Evitar conflitos de nomes de arquivo
.PHONY: all clean

tests-directory = ./test_cases
test: $(TARGET)
	@for input_file in $(tests-directory)/*.in; do \
		base_name=$$(basename $$input_file .in); \
		output_file=$(tests-directory)/$$base_name.out; \
		echo "\nExecuting test case: $$base_name"; \
		./programa < $$input_file > output_temp.out; \
		diff_output=$$(diff -ub output_temp.out $$output_file); \
		if [ -z "$$diff_output" ]; then \
			echo "	✅ Test succeed!"; \
		else \
			echo "	❌ Test failed!"; \
			echo "$$diff_output"; \
		fi; \
		rm output_temp.out; \
	done
	@rm -f $(OBJECTS) $(TARGET)