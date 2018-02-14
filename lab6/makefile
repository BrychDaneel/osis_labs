CC=gcc
LIBS=-lpthread
CFLAGS=-c -Wall -I include
INCLUDE_DIR=include
SOURCE_DIR=src
BUILD_DIR=build
DIST_DIR=dist

SERVER_NAME=server
TCP_CLIENT_NAME=client_tcp
UDP_CLIENT_NAME=client_udp

SERVER=$(DIST_DIR)/$(SERVER_NAME)
TCP_CLIENT=$(DIST_DIR)/$(TCP_CLIENT_NAME)
UDP_CLIENT=$(DIST_DIR)/$(UDP_CLIENT_NAME)

.PHONY : all
all: $(SERVER) $(TCP_CLIENT) $(UDP_CLIENT)

$(SERVER): $(BUILD_DIR)/server_main.o $(BUILD_DIR)/tcp_server.o $(BUILD_DIR)/udp_server.o
	$(CC) $^ $(LIBS) -o $@

$(TCP_CLIENT): $(BUILD_DIR)/tcp_client_main.o
	$(CC) $^ $(LIBS) -o $@

$(UDP_CLIENT): $(BUILD_DIR)/udp_client_main.o
	$(CC) $^ $(LIBS) -o $@

$(BUILD_DIR)/tcp_client_main.o: $(SOURCE_DIR)/tcp_client_main.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/tcp_client_main.c -o $@

$(BUILD_DIR)/udp_client_main.o: $(SOURCE_DIR)/udp_client_main.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/udp_client_main.c -o $@

$(BUILD_DIR)/server_main.o: $(SOURCE_DIR)/server_main.c $(INCLUDE_DIR)/tcp_server.h $(INCLUDE_DIR)/udp_server.h
	$(CC) $(CFLAGS) $(SOURCE_DIR)/server_main.c -o $@

$(BUILD_DIR)/tcp_server.o: $(SOURCE_DIR)/tcp_server.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/tcp_server.c -o $@

$(BUILD_DIR)/udp_server.o: $(SOURCE_DIR)/udp_server.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/udp_server.c -o $@

.PHONY : clean
clean:
	rm -R $(BUILD_DIR)/* $(DIST_DIR)/*

.PHONY : run
run: $(SERVER)
	$(SERVER)
