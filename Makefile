#make file for algaec

#project name
TARGET      = libalgaec.a
TEST_TARGET = algaec_test

#directories
BIN  	= bin
SRC  	= src
OBJ  	= $(BIN)
LIB  	= lib
INCLUDE = $(SRC)/include
TEST 	= test
TEST_SRC = $(TEST)
TEST_OBJ = $(BIN)

#dependencies
#TEST_FRAMEWORK = $(LIB)/check

#files
SOURCES  := $(wildcard $(SRC)/*.c)
INCLUDES := $(wildcard $(SRC)/include)
# INCLUDES := $(wildcard $(SRC)/include/*.h)
OBJECTS  := $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)

TEST_SOURCES := $(wildcard $(TEST_SRC)/*.c)
TEST_INCLUDES := $(INCLUDES)
TEST_OBJECTS := $(TEST_SOURCES:$(TEST_SRC)/%.c=$(TEST_OBJ)/%.o)

#compiler and settings
CC  = gcc

CFLAGS = -std=c89 -Wall -I. -I$(INCLUDE)
CFLAGS_TEST = -std=c99 -Wall -I. -I$(TEST_INCLUDES) 

#linker and settings
LINKER = gcc
AR  = ar
ARFLAGS = -static
LFLAGS = -Wall -I. -lm -lc -I$(INCLUDES)
TEST_LFLAGS = -Wall -I. -lm -lcheck -I$(TEST_INCLUDES) -L./$(BIN) -lalgaec

#targets
all:	$(BIN)/$(TARGET)

test:   $(BIN)/$(TEST_TARGET)
		./$(BIN)/$(TEST_TARGET)

clean:
	rm -f $(OBJECTS) $(BIN)/$(TARGET) $(BIN)/$(TEST_TARGET) $(TEST_OBJECTS) 
	echo "Workspace clean!"

$(BIN)/$(TARGET): $(OBJECTS)
	@$(AR) rcs $(OBJECTS) -o $@
	@echo "Linking complete!"

# $(BIN)/$(TARGET): $(OBJECTS)
# 	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
# 	@echo "Linking complete!"

$(BIN)/$(TEST_TARGET): $(TEST_OBJECTS)
	@$(LINKER) $(TEST_OBJECTS) $(TEST_LFLAGS) -o $@
	@echo "Test linking complete!"

$(OBJECTS): $(OBJ)/%.o : $(SRC)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled sucessfully!"

$(TEST_OBJECTS): $(TEST_OBJ)/%.o : $(TEST_SRC)/%.c
	@$(CC) $(CFLAGS_TEST) -c $< -o $@
	@echo "Tests compiled sucessfully!"

