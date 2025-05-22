# === Configuration de base ===

CC := gcc
CFLAGS := -Wall -O2 -fPIC -I.

# === Détection ou forçage de l'OS cible ===

ifeq ($(OS),)
    OS := $(shell uname -s)
endif

ifeq ($(OS),Linux)
    TARGET_OS := linux
    LDFLAGS := -lX11
    SHARED_EXT := so
endif

ifeq ($(OS),Windows_NT)
    TARGET_OS := windows
    LDFLAGS := -lgdi32
    SHARED_EXT := dll
endif

ifeq ($(OS),ProfanOS)
    TARGET_OS := profanos
    LDFLAGS :=
    SHARED_EXT := so
endif

COMMON_SRC := $(wildcard src/common/*.c) $(wildcard src/common/*/*.c)
OS_SRC := $(wildcard src/$(TARGET_OS)/*.c)
SRC := $(COMMON_SRC) $(OS_SRC)
OBJ := $(SRC:.c=.o)

all: libkalos.a shared

libkalos.a: $(OBJ)
	ar rcs $@ $^

shared: $(OBJ)
ifneq ($(SHARED_EXT),none)
	$(CC) -shared -o libkalos.$(SHARED_EXT) $^ $(LDFLAGS)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f src/**/*.o libkalos-*.a libkalos.so libkalos.dll

test:
	make -C ./test/


.PHONY: all clean test shared