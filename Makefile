
output: ./obj/main.o
	g++ -static -L ./deps/SDL2-2.0.12/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc obj/main.o -o output.exe -mwindows

./obj/main.o: ./src/main.cpp
	g++ -c ./src/main.cpp -o ./obj/main.o -I ./deps/SDL2-2.0.12/i686-w64-mingw32/include