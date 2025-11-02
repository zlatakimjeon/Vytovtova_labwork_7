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
    MKDIR = if not exist $(subst /,\\,$(1)) mkdir $(subst /,\\,$(1))
    RM = rmdir /s /q $(subst /,\\,$(1))
    DEL = del /q $(subst /,\\,$(1))
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
	$(DEL) $(LIB)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(TEST): $(LIB) $(TEST_DIR)/test.c
	$(CC) $(CFLAGS) -L$(LIB_DIR) $(TEST_DIR)/test.c -lgraph -o $@$(EXE)

run: $(TEST)
	$(RUN)

clean:
	-$(call RM,$(OBJ_DIR))
	-$(call RM,$(LIB_DIR))
	-$(DEL) $(TEST)$(EXE)

.PHONY: all clean run
