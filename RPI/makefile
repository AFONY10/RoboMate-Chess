# This makefile was used when developing the program for debugging purposes

MAKEFLAGS += --no-print-directory

SRC_DIR := .
PIECES_DIR := Pieces
BUILD_DIR := build

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp $(PIECES_DIR)/*.cpp)
DEP_FILES := $(addprefix $(BUILD_DIR)/,$(CPP_FILES:.cpp=.d))
OBJECTS := $(addprefix $(BUILD_DIR)/,$(CPP_FILES:.cpp=.o))
EXECUTABLE := RoboMate_RPI
CXX := g++
CXXFLAGS := -std=c++17 

all: $(EXECUTABLE)

-include $(DEP_FILES)

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking..."
	@$(CXX) -o $@ $^
	@echo "Compiling done"

$(BUILD_DIR)/%.o: %.cpp
	@echo "Compiling object of $<..."
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.d: %.cpp
	@echo "Compiling dependency of $<..."
	@mkdir -p $(@D)
	@$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	@$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

clean:
	@echo "Deleting $(EXECUTABLE) and $(BUILD_DIR) folder"
	@rm -rf $(EXECUTABLE) $(BUILD_DIR)

help:
	@echo "Available targets:"
	@echo "	all		: Compile the program (default target)"
	@echo "	clean	: Remove object files, the executable, and dependency files"
	@echo "	help	: Print this help message"

.PHONY: all clean