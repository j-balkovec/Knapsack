# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++20 \
					 -pedantic \
					 -g \
           -Wall \
           -Wextra \
					 -Wno-unused-const-variable \
					 -Wno-unused-variable \
					 -Wno-unused-parameter \
           -O3 \
           -I. \
           -ITools \
					 -I/opt/homebrew/Cellar/fmt/11.0.2/include \
           -I/opt/homebrew/Cellar/spdlog/1.15.0/include \
					 -arch arm64
           
#<bug>: -static is new
LDFLAGS = -L/opt/homebrew/Cellar/fmt/11.0.2/lib \
					-L/opt/homebrew/Cellar/spdlog/1.15.0/lib \
					-arch arm64

LIBS = -lfmt -lspdlog 

#LIBS = /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a /opt/homebrew/Cellar/spdlog/1.15.0/lib/libspdlog.a

# Directories
ALGO_DIR = Algorithms
HEUR_DIR = Heuristics
BIN_DIR = bin
OBJ_DIR = obj
TOOLS_DIR = Tools

# Source files
ALGO_SRCS = $(wildcard $(ALGO_DIR)/*.cpp)
HEUR_SRCS = $(wildcard $(HEUR_DIR)/*.cpp)
MAIN_SRC = main.cpp
UTILITY_SRC = $(TOOLS_DIR)/Utility.cpp
LOGGER_SRC = $(TOOLS_DIR)/Logger.cpp
BENCHMARK_SRC = $(TOOLS_DIR)/Benchmark.cpp

# Object files
ALGO_OBJS = $(patsubst $(ALGO_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(ALGO_SRCS))
HEUR_OBJS = $(patsubst $(HEUR_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(HEUR_SRCS))
MAIN_OBJ = $(OBJ_DIR)/main.o
UTILITY_OBJ = $(OBJ_DIR)/Utility.o
LOGGER_OBJ = $(OBJ_DIR)/Logger.o
BENCHMARK_OBJ = $(OBJ_DIR)/Benchmark.o

# Executable
MAIN_EXEC = $(BIN_DIR)/main

# Color Definitions
RESET_COLOR = \033[0m
GREEN_COLOR = \033[32m
CYAN_COLOR = \033[36m
YELLOW_COLOR = \033[33m
MAGENTA_COLOR = \033[35m
RED_COLOR = \033[31m
BOLD = \033[1m
UNDERLINE = \033[4m

# Default target
all: $(BIN_DIR) $(OBJ_DIR) $(MAIN_EXEC)

# Create directories
$(BIN_DIR):
	@echo "$(CYAN_COLOR)[INFO]: Creating $(BIN_DIR) directory...$(RESET_COLOR)"
	@mkdir -p $(BIN_DIR)
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: Directory $(BIN_DIR) created!$(RESET_COLOR)"

$(OBJ_DIR):
	@echo "$(CYAN_COLOR)[INFO]: Creating $(OBJ_DIR) directory...$(RESET_COLOR)"
	@mkdir -p $(OBJ_DIR)
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: Directory $(OBJ_DIR) created!$(RESET_COLOR)"

# Compile main object file
$(MAIN_OBJ): $(MAIN_SRC)
	@echo "$(MAGENTA_COLOR)[BUILD]: Compiling main.cpp...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: main.cpp compiled!$(RESET_COLOR)"

# Compile utility object file
$(UTILITY_OBJ): $(UTILITY_SRC)
	@echo "$(MAGENTA_COLOR)[BUILD]: Compiling Utility.cpp...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: Utility.cpp compiled!$(RESET_COLOR)"

# Compile logger object file
$(LOGGER_OBJ): $(LOGGER_SRC)
	@echo "$(MAGENTA_COLOR)[BUILD]: Compiling Logger.cpp...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: Logger.cpp compiled!$(RESET_COLOR)"

# Compile benchmark object file
$(BENCHMARK_OBJ): $(BENCHMARK_SRC)
	@echo "$(MAGENTA_COLOR)[BUILD]: Compiling Benchmark.cpp...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: Benchmark.cpp compiled!$(RESET_COLOR)"

# Compile algorithm source files to object files
$(OBJ_DIR)/%.o: $(ALGO_DIR)/%.cpp
	@echo "$(CYAN_COLOR)[BUILD]: Compiling algorithm file: $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: $(notdir $<) compiled!$(RESET_COLOR)"

# Compile heuristics source files to object files
$(OBJ_DIR)/%.o: $(HEUR_DIR)/%.cpp
	@echo "$(CYAN_COLOR)[BUILD]: Compiling heuristic file: $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: $(notdir $<) compiled!$(RESET_COLOR)"

# Link main executable with all object files
$(MAIN_EXEC): $(MAIN_OBJ) $(ALGO_OBJS) $(HEUR_OBJS) $(UTILITY_OBJ) $(LOGGER_OBJ) $(BENCHMARK_OBJ)
	@echo "$(YELLOW_COLOR)[BUILD]: Linking object files to create the executable...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: Executable $(MAIN_EXEC) created successfully!$(RESET_COLOR)"

# Clean up build files
clean:
	@echo "$(RED_COLOR)[CLEAN]: Cleaning up build files...$(RESET_COLOR)"
	@rm -rf $(BIN_DIR) $(OBJ_DIR)
	@echo
	@echo "$(GREEN_COLOR)[SUCCESS]: Clean up complete!$(RESET_COLOR)"

run:
	@echo
	@echo "$(YELLOW_COLOR)[RUN]: Running $(MAIN_EXEC)...$(RESET_COLOR)"
	@./$(MAIN_EXEC)

build: $(MAIN_EXEC)

debug: CXXFLAGS += -g
debug: $(MAIN_EXEC)

rebuild: clean build

# test: TODO

stats:
	@echo "$(CYAN_COLOR)[STATS]: File sizes...$(RESET_COLOR)"
	@du -sh $(OBJ_DIR)/*
	@du -sh $(MAIN_EXEC)

check:
	@echo "$(CYAN_COLOR)[CHECK]: Running static analysis...$(RESET_COLOR)"
	clang-tidy $(ALGO_SRCS) $(HEUR_SRCS) $(MAIN_SRC)

version:
	@echo "$(CYAN_COLOR)[VERSION]: Project Version 1.0.0$(RESET_COLOR)"
	@echo "$(CYAN_COLOR)[VERSION]: Compiler Version $(shell clang++ --version | head -n 1)$(RESET_COLOR)"

zip:
	@echo "$(CYAN_COLOR)[ZIP]: Creating project archive...$(RESET_COLOR)"
	@zip -r project.zip ./*
	@echo "$(GREEN_COLOR)[SUCCESS]: Project archived as project.zip$(RESET_COLOR)"

dependencies:
	@echo "$(CYAN_COLOR)[DEPENDENCIES]: Listing installed dependencies...$(RESET_COLOR)"
	brew list fmt spdlog

# Phony targets
.PHONY: all clean build run debug rebuild stats check version zip dependencies
