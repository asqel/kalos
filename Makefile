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

# === Gestion des sources ===

COMMON_SRC := $(wildcard src/common/*.c) $(wildcard src/common/*/*.c)
OS_SRC := $(wildcard src/$(TARGET_OS)/*.c)
SRC := $(COMMON_SRC) $(OS_SRC)
OBJ := $(SRC:.c=.o)

# === Cibles principales ===

all: libkalos-$(TARGET_OS).a shared

libkalos-$(TARGET_OS).a: $(OBJ)
	ar rcs $@ $^

shared: $(OBJ)
ifneq ($(SHARED_EXT),none)
	$(CC) -shared -o libkalos-$(TARGET_OS).$(SHARED_EXT) $^ $(LDFLAGS)
endif

# === Règle de compilation .o ===

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

# === Nettoyage ===

clean:
	rm -f src/**/*.o libkalos-*.a libkalos-*.so libkalos-*.dll

