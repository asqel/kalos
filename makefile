
COMP = gcc

COMMON_FILES := $(wildcard src/common/*.c) $(wildcard src/common/*/*.c)
OUT_DIR = out

build_common:
	$(foreach file, $(COMMON_FILES),  \
		gcc -c $(file) -o temp/common/$(basename $(notdir $(file))).o \
	)

setup_linux:
	mkdir -p temp
	mkdir -p out
	mkdir -p temp/common

linux: setup_linux build_common
	$(foreach file, $(wildcard src/linux/*.c) $(wildcard src/linux/*/*.c),  \
		gcc -c $(file) -o temp/$(basename $(notdir $(file))).o -lx11 \
	)
	ar rcs out/kalos.a temp/*.o temp/*/*.o

windows: common
	gcc -c -o out/kalos_windows.o src/windows/windows.c -lgdi32
	ar rcs out/kalos_windows.a out/kalos_windows.o out/common.o
	del "out\kalos_windows.o"
	del "out\common.o"


test_linux: linux
	gcc main.c -o test/main -Lout -l:kalos.a -lX11 -lm
	./test/main

test_windows: windows
	gcc main.c -o test/main.exe -Lout -l:kalos.a -lgdi32
	./test/main



clean:
	rm -rf out/*
	rm -rf temp/*.o
	rm -rf temp/*/*.o
