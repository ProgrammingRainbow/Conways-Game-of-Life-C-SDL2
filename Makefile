TARGET			= game-of-life
BUILD_DIR		= .build
SRC_DIR			?= src
CC				?= gcc

CFLAGS_BASE     = -std=c99 -Wstrict-aliasing=2 -Wall -Wextra -Werror \
                  -Wpedantic -Wwrite-strings -Wconversion -Wmissing-declarations \
                  -Wmissing-include-dirs -Wfloat-equal -Wsign-compare -Wundef \
                  -Wcast-align -Wswitch-default -Wimplicit-fallthrough \
                  -Wempty-body -Wuninitialized -Wmisleading-indentation \
                  -Wshadow -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition

CFLAGS_RELEASE	= -O3 -march=native -flto=auto -fno-plt -fomit-frame-pointer

CFLAGS_DEBUG 	= -O0 -g3 -ggdb3 -fno-strict-aliasing -fstack-protector-strong \
				  -DDEBUG -fno-omit-frame-pointer

LDLIBS_BASE		=

LDLIBS_RELEASE	= -flto

LDLIBS_DEBUG	=

SRCS			= $(wildcard $(SRC_DIR)/*.c)
OBJS			= $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))
DEPS			= $(OBJS:.o=.d)

ifeq ($(OS),Windows_NT)
	PKG_CONFIG := $(shell where pkg-config >NUL 2>&1 && echo "yes" || echo "no")
	CLEAN 		= del /f $(TARGET).exe & if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	MKDIR		= if not exist $(BUILD_DIR) mkdir
else
	CFLAGS_DEBUG	+= -fsanitize=address -fsanitize-address-use-after-scope \
					   -ftrapv
	LDLIBS_DEBUG	+= -fsanitize=address -fsanitize-address-use-after-scope
	PKG_CONFIG := $(shell command -v pkg-config >/dev/null 2>&1 && echo "yes" || echo "no")
	CLEAN		= $(RM) -f $(TARGET) && $(RM) -rf $(BUILD_DIR)
	MKDIR		= mkdir -p $(BUILD_DIR)
endif

ifeq ($(PKG_CONFIG),yes)
    CFLAGS_BASE += $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
    LDLIBS_BASE += $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)
else
    $(error "pkg-config is not available. Please install pkg-config.")
endif

CFLAGS		?= $(CFLAGS_BASE) $(CFLAGS_DEBUG)
LDLIBS		?= $(LDLIBS_BASE) $(LDLIBS_DEBUG)

$(BUILD_DIR):
	$(MKDIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDLIBS)

-include $(DEPS)

.PHONY: all clean run rebuild release

all: $(TARGET)

release: CFLAGS = $(CFLAGS_BASE) $(CFLAGS_RELEASE)
release: LDLIBS = $(LDLIBS_BASE) $(LDLIBS_RELEASE)
release: all

clean:
	$(CLEAN)

run: $(TARGET)
	./$<

rebuild: clean all
