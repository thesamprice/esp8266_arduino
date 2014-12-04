

# Base directory for the compiler
XTENSA_TOOLS_ROOT = $(ESP_SDK_BASE)/bin

CFLAGS   := -ggdb -D__GNU_VISIBLE -Os -g -O2 -Wpointer-arith -Werror -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -mtext-section-literals  -D__ets__ -DICACHE_FLASH $(OS_CFLAGS)
CFLAGS += -Iinclude
CFLAGS += -Iboards/esp8266
#CFLAGS += -I/opt/Espressif/ESP8266_SDK/include
CFLAGS += -I/home/sprice5/src/alex/Mote/Software/include
CXXFLAGS := $(CXXFLAGS) $(CFLAGS)

CFLAGS +=  -std=c99
#Compression flags
#build in support for file compression but don't compress anything for now.
CFLAGS		:= $(CFLAGS) -DEFS_HEATSHRINK
CXXFLAGS += -DEFS_HEATSHRINK

BUILD_BASE	= build

CC		:= $(XTENSA_TOOLS_ROOT)/xtensa-lx106-elf-gcc
CXX     := $(XTENSA_TOOLS_ROOT)/xtensa-lx106-elf-g++

SRC := $(wildcard src/*.c)
SRC += $(wildcard src/*.cpp)

OBJ := $(patsubst %.c,$(BUILD_BASE)/%.o,$(SRC))
OBJ += $(patsubst %.cpp,$(BUILD_BASE)/%.o,$(SRC))
TARGET = "wiring"

$(TARGET): $(OBJ)
	@echo "LD $@"
$(BUILD_BASE):
	@mkdir -p $@

# C compiler to build .o from .c in $(BUILD_DIR)
$(BUILD_BASE)/%.o : ./%.c
	@echo "CC $<"
	@$(CC) $(INCDIR) $(MODULE_INCDIR) $(EXTRA_INCDIR) $(SDK_INCDIR) $(CFLAGS) -c $< -o $@

# CPP compiler to build .o from .cpp in $(BUILD_DIR)
# Note: Calls standard $(CC) - gcc will invoke g++ as appropriate
$(BUILD_BASE)/%.o : ./%.cpp
	@echo "CXX $<"
	@$(CXX) $(INCDIR) $(MODULE_INCDIR) $(EXTRA_INCDIR) $(SDK_INCDIR) $(CXXFLAGS)  -c $< -o $@

clean:
	@rm -rf $(BUILD_BASE)/*.a
	@rm -rf $(BUILD_BASE)/*.o	
