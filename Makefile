# Makefile variables
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = src/*.cpp \
			src/ECS/*.cpp \
			src/Game/*.cpp \
			src/Logger/*cpp
LINKER_FLAGS = -lSDL2 \
			   -lSDL2_image \
			   -lSDL2_ttf \
			   -lSDL2_mixer \
			   -llua5.4
PROGRAM_NAME = gameEngine

# Makefile rules
build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(PROGRAM_NAME)

run:
	./$(PROGRAM_NAME)

clean:
	rm $(PROGRAM_NAME)