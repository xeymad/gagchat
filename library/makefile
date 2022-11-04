TARGET_EXEC := test

BUILD_DIR := ./build
SRC_DIRS := ./src
INC_DIR := ./include

# Find all the C we want to compile
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# String substitution for every C file.
# As an example, hello.c turns into ./build/hello.o
OBJS_O := $(SRCS:.c=.o)
OBJS := $(OBJS_O:%=$(BUILD_DIR)/%)

# Every folder in ./include will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(INC_DIR) -type d)
# Add a prefix to INC_DIRS. So module A would become -I moduleA.
INC_FLAGS := $(addprefix -I ,$(INC_DIRS))

# List of flag for C compiler
CFLAGS := $(INC_FLAGS)

LDFLAGS := -lm

# Build All Libraries
.DELETE_ON_ERROR:
all_libraries : $(OBJS)

# The final build step.
test: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	-rm -r $(BUILD_DIR)
	
	