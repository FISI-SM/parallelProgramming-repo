CXX = g++
CC  = gcc

CXXFLAGS = `fltk-config --cxxflags` -Iinclude
CFLAGS   = -Iinclude
LDFLAGS  = `fltk-config --ldflags`

SRC_DIR  = src
APP_DIR  = app
OBJ_DIR  = obj
BIN      = nbody_fltk

OBJS = $(OBJ_DIR)/nbody_basic.o \
       $(OBJ_DIR)/nbody_view.o  \
       $(OBJ_DIR)/main.o

all: $(BIN)

$(OBJ_DIR)/nbody_basic.o: $(SRC_DIR)/nbody_basic.c include/nbody_basic.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/nbody_view.o: $(SRC_DIR)/nbody_view.cpp include/nbody_basic.h include/nbody_view.h
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(APP_DIR)/main.cpp include/nbody_view.h
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $(BIN) $(LDFLAGS)

run: all
	./$(BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN)
