common:
	gcc -c -o out/common.o src/common/common.c

linux: common
	gcc -c -o kalos_linux.o src/linux/linux.c -lx11
	ar rcs kalos_linux.a kalos_linux.o out/common.o
	mv kalos_linux.a out/kalos_linux.a
	rm kalos_linux.o
	rm out/common.o

windows: common
	gcc -c -o out/kalos_windows.o src/windows/windows.c -lgdi32
	ar rcs out/kalos_windows.a out/kalos_windows.o out/common.o
	del "out\kalos_windows.o"
	del "out\common.o"

test_linux: linux
	gcc main.c -o test/main -Lout -l:kalos_linux.a -lX11 
	./test/main

test_windows: windows
	gcc main.c -o test/main.exe -Lout -l:kalos_windows.a -lgdi32
	./test/main
