CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
AR = ar
ARFLAGS = rcs

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = test

LIB = $(LIB_DIR)/libgraph.a
OBJS = $(OBJ_DIR)/graph.o
TEST = $(TEST_DIR)/run

ifeq ($(OS),Windows_NT)
    EXE = .exe
    MKDIR = powershell -Command "if (!(Test-Path $(1))) { New-Item -ItemType Directory -Force -Path $(1) | Out-Null }"
    RM = powershell -Command "if (Test-Path $(1)) { Remove-Item -Recurse -Force $(1) }"
    DEL = powershell -Command "if (Test-Path $(1)) { Remove-Item -Force $(1) }"
    RUN = $(TEST)$(EXE)
else
    EXE =
    MKDIR = mkdir -p $(1)
    RM = rm -rf $(1)
    DEL = rm -f $(1)
    RUN = ./$(TEST)
endif

all: clean $(LIB) $(TEST)

$(OBJ_DIR):
	$(call MKDIR,$(OBJ_DIR))

$(LIB_DIR):
	$(call MKDIR,$(LIB_DIR))

$(OBJ_DIR)/graph.o: $(SRC_DIR)/graph.c include/graph.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS) | $(LIB_DIR)
	$(call DEL,$(LIB))
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(TEST): $(LIB) $(TEST_DIR)/test.c
	$(CC) $(CFLAGS) -L$(LIB_DIR) $(TEST_DIR)/test.c -lgraph -o $@$(EXE)

run: $(TEST)
	$(RUN)

clean:
	-$(call RM,$(OBJ_DIR))
	-$(call RM,$(LIB_DIR))
	-$(call DEL,$(TEST)$(EXE))

.PHONY: all clean run
