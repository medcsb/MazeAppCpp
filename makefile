# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I./libs/SFML-2.6.1/include -I./$(MAZE_HEADERS_DIR) -I./$(GUI_HEADERS_DIR)
LDFLAGS = -L./libs/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
BIN_DIR = bin
MAZE_DIR = $(SRC_DIR)/maze
GUI_DIR = $(SRC_DIR)/gui
MAZE_HEADERS_DIR = $(MAZE_DIR)/headers
GUI_HEADERS_DIR = $(GUI_DIR)/headers

# Source files
MAZE_SOURCES = $(filter-out $(MAZE_DIR)/test.cpp, $(wildcard $(MAZE_DIR)/*.cpp))  # All .cpp files except test.cpp
MAZE_TEST_SOURCE = $(MAZE_DIR)/test.cpp  # test.cpp specifically
GUI_SOURCES = $(filter-out $(GUI_DIR)/main.cpp, $(wildcard $(GUI_DIR)/*.cpp))  # All .cpp files except main.cpp
GUI_MAIN_SOURCE = $(GUI_DIR)/main.cpp  # main.cpp specifically

# Object files
MAZE_OBJECTS = $(patsubst $(MAZE_DIR)/%.cpp, $(BIN_DIR)/%.o, $(MAZE_SOURCES))
MAZE_TEST_OBJECT = $(patsubst $(MAZE_DIR)/%.cpp, $(BIN_DIR)/%.o, $(MAZE_TEST_SOURCE))
GUI_OBJECTS = $(patsubst $(GUI_DIR)/%.cpp, $(BIN_DIR)/%.o, $(GUI_SOURCES))
GUI_MAIN_OBJECT = $(patsubst $(GUI_DIR)/%.cpp, $(BIN_DIR)/%.o, $(GUI_MAIN_SOURCE))

# Executables
MAZE_EXECUTABLE = $(BIN_DIR)/maze_test
GUI_EXECUTABLE = $(BIN_DIR)/maze_gui

# Targets
all: $(MAZE_EXECUTABLE) $(GUI_EXECUTABLE)

# Rule to build the maze test executable
$(MAZE_EXECUTABLE): $(MAZE_TEST_OBJECT) $(MAZE_OBJECTS)
	$(CXX) $(MAZE_TEST_OBJECT) $(MAZE_OBJECTS) -o $@ $(LDFLAGS)

# Rule to build the GUI application executable
$(GUI_EXECUTABLE): $(GUI_MAIN_OBJECT) $(GUI_OBJECTS) $(MAZE_OBJECTS) $(MAZE_TEST_OBJECT)
	$(CXX) $(GUI_MAIN_OBJECT) $(GUI_OBJECTS) $(MAZE_OBJECTS) -o $@ $(LDFLAGS)

# Rule to compile maze .cpp files to .o files
$(BIN_DIR)/%.o: $(MAZE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile GUI .cpp files to .o files
$(BIN_DIR)/%.o: $(GUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
ifeq ($(OS),Windows_NT)
	rm $(BIN_DIR)/*.o
	rm $(BIN_DIR)/*.exe
else
	rm -f $(BIN_DIR)/*.o $(MAZE_EXECUTABLE) $(GUI_EXECUTABLE)
endif

# Phony targets
.PHONY: all clean
