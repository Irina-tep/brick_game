# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -lncurses
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
UNAME=$(shell uname -s)
 

# Target executable
TARGET = tetris

ifeq ($(UNAME), Linux)
	LIBS=-lcheck -lm -lrt -lpthread -lsubunit
endif
ifeq ($(UNAME), Darwin)
	LIBS=-lcheck
endif

# Directories
BUILD_DIR = build
INSTALL_DIR = ../build
GUI_DIR = gui/cli
TETRIS_DIR = brick_game/tetris
DIST_SOURCES = $(TETRIS_DIR)/* $(GUI_DIR)/* tests/* dvi/* Makefile
TEST_DIR = tests

# Source files
TETRIS_SRCS=$(wildcard $(TETRIS_DIR)/*.c)
TEST_SRCS=$(wildcard $(TEST_DIR)/*.c) $(TETRIS_DIR)/game_info.c $(TETRIS_DIR)/tetris_fsm.c $(TETRIS_DIR)/user_input.c $(wildcard $(GUI_DIR)/*.c)
GUI_SRCS=$(wildcard $(GUI_DIR)/*.c)
ALL_SRCS= $(TETRIS_SRCS) $(GUI_SRCS)
HEADERS=$(wildcard $(TETRIS_DIR)/*.h) $(wildcard $(GUI_DIR)/*.h)

# Object files
TETRIS_OBJS = $(TETRIS_SRCS:%.c=$(BUILD_DIR)/%.o)
GUI_OBJS = $(GUI_SRCS:%.c=$(BUILD_DIR)/%.o)
TOBJS = $(TEST_SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS = $(TETRIS_OBJS) $(GUI_OBJS)


# Default target
all: $(BUILD_DIR) $(TARGET)

run:$(BUILD_DIR) $(TARGET)
	./$(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/brick_game/tetris
	mkdir -p $(BUILD_DIR)/gui/cli

# Build executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(CFLAGS)

# Build object files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(TETRIS_DIR) -I$(GUI_DIR) -c $< -o $@

install: $(BUILD_DIR) $(TARGET)
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/$(TARGET)
	cp max_score.txt $(INSTALL_DIR)/max_score.txt
	@echo "Installed"

uninstall:
	@rm -rf $(INSTALL_DIR)
	@echo "Unstalled"

dvi:
	@open dvi/index.html > /dev/null 2>&1
	@echo "Documentation opening..."

dist: clean
	@tar -czf tetris.tar.gz $(DIST_SOURCES) > /dev/null 2>&1
	@echo "Archive created"

test: 
	mkdir -p $(BUILD_DIR)/tests
	$(CC) -I$(SRC_DIR) -I$(GUI_DIR) -I$(TEST_DIR) $(TEST_SRCS) -o $(BUILD_DIR)/tests/test $(LDFLAGS) $(CFLAGS) $(LIBS)
	./$(BUILD_DIR)/tests/test

gcov_report: clean
	mkdir -p $(BUILD_DIR)/report
	$(CC) -I$(SRC_DIR) -I$(GUI_DIR) -I$(TEST_DIR) $(TEST_SRCS) -o $(BUILD_DIR)/report/test_gc $(LDFLAGS) $(CFLAGS) $(TEST_FLAGS) $(GCOV_FLAGS) $(LIBS)
	./build/report/test_gc 
	gcovr -r . --gcov-executable gcov --exclude "test/*" --exclude ".*updateUserAction.*" --html --html-details -o $(BUILD_DIR)/report/gcov_report.html --exclude-unreachable-branches --exclude-branches-by-pattern=".*"
	@open $(BUILD_DIR)/report/gcov_report.html > /dev/null 2>&1
#	If you are working through the WSL, you need:
#	sudo sudo apt install wslu
# 	@wslview $(BUILD_DIR)/report/gcov_report.html > /dev/null 2>&1

valgrind:
	valgrind -s --tool=memcheck --track-origins=yes --leak-check=yes ./tetris

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

check_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n  $(ALL_SRCS) $(HEADERS) $(TEST_DIR)/*.c
	rm -rf .clang-format

fix_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i  $(ALL_SRCS) $(HEADERS) $(TEST_DIR)/*.c
	rm -rf .clang-format

# Rebuild from scratch
re: clean all

# Phony targets
.PHONY: all clean re dvi