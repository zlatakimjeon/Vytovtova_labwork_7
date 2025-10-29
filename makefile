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
    MKDIR = if not exist $(subst /,\\,$(1)) mkdir $(subst /,\\,$(1))
    RM = rmdir /s /q $(subst /,\\,$(1))
else
    MKDIR = mkdir -p $(1)
    RM = rm -rf $(1)
endif

all: $(LIB) $(TEST)

$(OBJ_DIR):
	$(call MKDIR,$(OBJ_DIR))

$(LIB_DIR):
	$(call MKDIR,$(LIB_DIR))

$(LIB): $(OBJ_DIR) $(LIB_DIR) $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(OBJ_DIR)/graph.o: $(SRC_DIR)/graph.c include/graph.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST): $(LIB) $(TEST_DIR)/test.c
	$(CC) $(CFLAGS) -L$(LIB_DIR) $(TEST_DIR)/test.c -lgraph -o $@

run: $(TEST)
	./$(TEST)

clean:
	-$(call RM,$(OBJ_DIR))
	-$(call RM,$(LIB_DIR))
	-del $(subst /,\\,$(TEST))

.PHONY: all clean run
