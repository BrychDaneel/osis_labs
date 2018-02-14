CC=gcc
LIBS=
CFLAGS=-c -Wall -I include
INCLUDE_DIR=include
SOURCE_DIR=src
BUILD_DIR=build
DIST_DIR=dist

EXECUTABLE_NAME=lab4

EXECUTABLE=$(DIST_DIR)/$(EXECUTABLE_NAME)

.PHONY : all
all: $(EXECUTABLE)

$(EXECUTABLE): $(BUILD_DIR)/main.o $(BUILD_DIR)/procinfo.o
	$(CC) $^ $(LIBS) -o $@

$(BUILD_DIR)/procinfo.o: $(SOURCE_DIR)/procinfo.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/procinfo.c -o $@

$(BUILD_DIR)/main.o: $(INCLUDE_DIR)/procinfo.h $(SOURCE_DIR)/main.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.c -o $@

.PHONY : clean
clean:
	rm -R $(BUILD_DIR)/* $(DIST_DIR)/*

.PHONY : run
run: $(EXECUTABLE)
	$(EXECUTABLE)
