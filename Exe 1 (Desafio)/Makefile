# Detect OS
ifeq ($(OS),Windows_NT)
    RM = del /q /s
    MD = @mkdir 2> nul || echo.
    EXE = .exe
else
    RM = rm -rf
    MD = mkdir -p
    EXE =
endif

# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror
LDFLAGS  := -lstdc++ -lm
BUILD    := build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)
TARGET   := app$(EXE)
INCLUDE  := -Iinclude
SRC      := $(wildcard src/*.cpp)

# Object files
OBJECTS := $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: build $(APP_DIR)/$(TARGET)

# Rule to compile .cpp files to .o files
$(OBJ_DIR)/%.o: src/%.cpp
	$(MD) $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

# Rule to link .o files to create the executable
$(APP_DIR)/$(TARGET): $(OBJECTS)
	$(MD) $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ $(OBJECTS)

.PHONY: all build clean debug release run

# Build target (creates directories if they don't exist)
build:
	$(MD) $(APP_DIR)
	$(MD) $(OBJ_DIR)

# Debug build
debug: CXXFLAGS += -DDEBUG -g
debug: all

# Release build
release: CXXFLAGS += -O3
release: all

# Clean up build artifacts
clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(APP_DIR)/*
	@sleep 1  # Small pause to ensure file system operations complete

# Run the executable
run:
	$(APP_DIR)/$(TARGET)
