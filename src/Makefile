debug/sfml-game: debug/main.o
	g++ debug/main.o -o ../bin/debug/sfml-game -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

debug/main.o: debug/main.cpp
	cd debug && g++ -c -g main.cpp

clean:
	rm -rf ../src/release/*.o ../src/debug/*.o ../bin/debug/sfml-game ../bin/release/sfml-game