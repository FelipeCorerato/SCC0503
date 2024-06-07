CC = g++

clean:
	rm -r lib/*/*.o $(program)

compile: main.cpp ./lib/MangaDatabase.cpp
	$(CC) -std=c++17 -o manga_app main.cpp ./lib/MangaDatabase.cpp

exec:
	$(CC) -std=c++17 -o manga_app main.cpp ./lib/MangaDatabase.cpp
	./manga_app
