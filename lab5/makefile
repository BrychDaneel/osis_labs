CC=gcc
LIBS=-lpthread
CFLAGS=-c -Wall -I include
INCLUDE_DIR=include
SOURCE_DIR=src
BUILD_DIR=build
DIST_DIR=dist

EXECUTABLE_NAME=lab5

EXECUTABLE=$(DIST_DIR)/$(EXECUTABLE_NAME)

.PHONY : all
all: $(EXECUTABLE)

$(EXECUTABLE): $(BUILD_DIR)/main.o $(BUILD_DIR)/deamon.o $(BUILD_DIR)/tracker.o $(BUILD_DIR)/mylog.o
	$(CC) $^ $(LIBS) -o $@

$(BUILD_DIR)/deamon.o: $(SOURCE_DIR)/deamon.c $(INCLUDE_DIR)/mylog.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/deamon.c -o $@

$(BUILD_DIR)/tracker.o: $(SOURCE_DIR)/tracker.c $(INCLUDE_DIR)/mylog.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/tracker.c -o $@

$(BUILD_DIR)/mylog.o: $(SOURCE_DIR)/mylog.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/mylog.c -o $@


$(BUILD_DIR)/main.o: $(INCLUDE_DIR)/deamon.h $(INCLUDE_DIR)/tracker.h $(SOURCE_DIR)/main.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.c -o $@

.PHONY : clean
clean:
	rm -R $(BUILD_DIR)/* $(DIST_DIR)/*

.PHONY : run
run: $(EXECUTABLE)
	$(EXECUTABLE)
