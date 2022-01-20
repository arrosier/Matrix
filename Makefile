# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DEBUG_DIR = bin/debug

# Release build settings
EXE = $(BIN_DIR)/main
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
CXXFLAGS = -Wall -I $(SRC_DIR) -MMD -MP

# Debug build settings
DEBUG_EXE = $(DEBUG_DIR)/main
DEBUG_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(DEBUG_DIR)/%.o, $(SRC))
DEBUG_FLAGS = -I $(SRC_DIR) -g

.PHONY: all debug clean prep remake

# Default build
all: prep $(EXE)

# Release rules
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

# Debug rules
debug: $(DEBUG_EXE)

$(DEBUG_EXE): $(DEBUG_OBJ)
	$(CXX) $(CXXFLAGS) -g $^ -o $@

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -g $< -o $@

-include $(DEBUG_OBJ:.o=.d)

# Other rules
clean:
	@$(RM) $(EXE) $(OBJ_DIR)/* $(DEBUG_DIR)/*

prep:
	@mkdir -p $(SRC_DIR) $(OBJ_DIR) $(BIN_DIR) $(DEBUG_DIR)

remake: clean all
