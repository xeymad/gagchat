TARGET_EXEC := test

BUILD_DIR := ./build
SRC_DIRS := ./src
INC_DIR := ./include

# Find all the C we want to compile
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# String substitution for every C file.
# As an example, hello.c turns into hello.o
OBJS_FILE := $(patsubst $(SRC_DIRS)/%.c,%.o,$(SRCS))
OBJS_PATH := $(patsubst %,$(BUILD_DIR)/%,$(OBJS_FILE))

# Every folder in ./include will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(INC_DIR) -type d)
# Add a prefix to INC_DIRS. So module A would become -I moduleA.
INC_FLAGS := $(addprefix -I ,$(INC_DIRS))

# List of flag for C compiler
CFLAGS := $(INC_FLAGS)

LDFLAGS := -lm

print_all:
	@echo $(OBJS_PATH)
	@echo $(OBJS_FILE)

# Build All Libraries
.DELETE_ON_ERROR:
all_libraries : $(OBJS_PATH)

# The final build step.
test: all_libraries
	$(CC) -c -I $(INC_DIR) $(TARGET_EXEC).c
	$(CC) $(TARGET_EXEC).o $(OBJS_PATH) -o $(TARGET_EXEC) $(LDFLAGS)
	@rm $(TARGET_EXEC).o

# Build step for C source
$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	-rm -f -r $(BUILD_DIR)
	-rm -f $(TARGET_EXEC).o
	-rm -f $(TARGET_EXEC)
	
	