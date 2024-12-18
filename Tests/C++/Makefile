RESET_COLOR = \033[0m
GREEN_COLOR = \033[32m
CYAN_COLOR = \033[36m
YELLOW_COLOR = \033[33m
MAGENTA_COLOR = \033[35m
RED_COLOR = \033[31m
BOLD = \033[1m
UNDERLINE = \033[4m

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
           -I../../C++/Algorithms \
           -I../../C++/Heuristics \
           -I../../C++/Tools \
           -I/opt/homebrew/Cellar/fmt/11.0.2/include \
           -I/opt/homebrew/Cellar/spdlog/1.15.0/include \
           -arch arm64

LDFLAGS = -L/opt/homebrew/Cellar/fmt/11.0.2/lib \
          -L/opt/homebrew/Cellar/spdlog/1.15.0/lib \
          -arch arm64

LIBS = -lfmt -lspdlog

# Directories
SRC_DIR = .
ALGO_DIR = ../../C++/Algorithms
HEUR_DIR = ../../C++/Heuristics
TOOLS_DIR = ../../C++/Tools
OBJ_DIR = obj
BIN_DIR = bin

# Source files
ALGO_SRCS = $(wildcard $(ALGO_DIR)/*.cpp)
HEUR_SRCS = $(wildcard $(HEUR_DIR)/*.cpp)
TEST_SRCS = ACO_test.cpp SimulatedAnnealing_test.cpp
UTILITY_SRC = $(TOOLS_DIR)/Utility.cpp
LOGGER_SRC = $(TOOLS_DIR)/Logger.cpp
BENCHMARK_SRC = $(TOOLS_DIR)/Benchmark.cpp

# Object files
ALGO_OBJS = $(patsubst $(ALGO_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(ALGO_SRCS))
HEUR_OBJS = $(patsubst $(HEUR_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(HEUR_SRCS))
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))
UTILITY_OBJ = $(OBJ_DIR)/Utility.o
LOGGER_OBJ = $(OBJ_DIR)/Logger.o
BENCHMARK_OBJ = $(OBJ_DIR)/Benchmark.o

# Executables
ACO_EXE = $(BIN_DIR)/ACO_test
SA_EXE = $(BIN_DIR)/SimulatedAnnealing_test
TEST_EXECS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(TEST_SRCS))

# Default target
all: $(BIN_DIR) $(OBJ_DIR) $(TEST_EXECS)

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

# Compile algorithm object files
$(OBJ_DIR)/%.o: $(ALGO_DIR)/%.cpp
	@echo "$(CYAN_COLOR)[BUILD]: Compiling $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: $(notdir $<) compiled!$(RESET_COLOR)"
	@echo

# Compile heuristic object files
$(OBJ_DIR)/%.o: $(HEUR_DIR)/%.cpp
	@echo "$(CYAN_COLOR)[BUILD]: Compiling $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: $(notdir $<) compiled!$(RESET_COLOR)"
	@echo

# Compile test object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(CYAN_COLOR)[BUILD]: Compiling $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: ACO_test.cpp & SimulatedAnnealing_test.cpp compiled!$(RESET_COLOR)"
	@echo

# Compile utility object file
$(UTILITY_OBJ): $(UTILITY_SRC)
	@echo "$(CYAN_COLOR)[BUILD]: Compiling $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: Utility.cpp compiled!$(RESET_COLOR)"
	@echo

# Compile logger object file
$(LOGGER_OBJ): $(LOGGER_SRC)
	@echo "$(CYAN_COLOR)[BUILD]: Compiling $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: Logger.cpp compiled!$(RESET_COLOR)"
	@echo

# Compile benchmark object file
$(BENCHMARK_OBJ): $(BENCHMARK_SRC)
	@echo "$(CYAN_COLOR)[BUILD]: Compiling $<...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: Benchmark.cpp compiled!$(RESET_COLOR)"
	@echo

# Link executables
$(ACO_EXE): $(OBJ_DIR)/ACO_test.o $(ALGO_OBJS) $(HEUR_OBJS) $(UTILITY_OBJ) $(LOGGER_OBJ) $(BENCHMARK_OBJ)
	@echo "$(CYAN_COLOR)[LINK]: Linking ACO_test executable...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: ACO_test executable created!$(RESET_COLOR)"
	@echo

$(SA_EXE): $(OBJ_DIR)/SimulatedAnnealing_test.o $(ALGO_OBJS) $(HEUR_OBJS) $(UTILITY_OBJ) $(LOGGER_OBJ) $(BENCHMARK_OBJ)
	@echo "$(CYAN_COLOR)[LINK]: Linking SimulatedAnnealing_test executable...$(RESET_COLOR)"
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LIBS) -o $@
	@echo "$(GREEN_COLOR)[SUCCESS]: SimulatedAnnealing_test executable created!$(RESET_COLOR)"
	@echo

# Clean up build files
clean:
	@echo "$(YELLOW_COLOR)[CLEAN]: Cleaning up...$(RESET_COLOR)"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "$(GREEN_COLOR)[SUCCESS]: Clean up complete!$(RESET_COLOR)"

# Compile
all: $(BIN_DIR) $(OBJ_DIR) $(ACO_EXE) $(SA_EXE)

# Run ACO_test
run_aco: $(ACO_EXE)
	@echo
	@echo "$(CYAN_COLOR)[RUN]: Running ACO_test...$(RESET_COLOR)"
	@echo
	@./$(ACO_EXE)

# Run SimulatedAnnealing_test
run_sa: $(SA_EXE)
	@echo
	@echo "$(CYAN_COLOR)[RUN]: Running SimulatedAnnealing_test...$(RESET_COLOR)"
	@echo
	@./$(SA_EXE)

# Build ACO executable (rebuild only ACO_test executable)
build_aco: $(ACO_EXE)
	@echo
	@echo "$(CYAN_COLOR)[BUILD]: Rebuilding ACO_test executable...$(RESET_COLOR)"
	@echo

# Build SA executable (rebuild only SimulatedAnnealing_test executable)
build_sa: $(SA_EXE)
	@echo
	@echo "$(CYAN_COLOR)[BUILD]: Rebuilding SimulatedAnnealing_test executable...$(RESET_COLOR)"
	@echo

run_both: $(SA_EXE) $(ACO_EXE)
	@echo
	@echo "$(CYAN_COLOR)[RUN]: Running ACO_test ...$(RESET_COLOR)"
	@echo
	@./$(ACO_EXE)
	@echo
	@echo "$(CYAN_COLOR)[RUN]: Running SimulatedAnnealing_test ...$(RESET_COLOR)"
	@./$(SA_EXE)
	@echo

# Phony targets
.PHONY: all clean run_aco run_sa build_aco build_sa run_both