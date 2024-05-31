# Compiler
CC = gcc

# Compiler Flags

# Linker Flags
LDFLAGS = -lpcap

# Source and Object Files
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TARGET = $(BINDIR)/kraken

# Default Target
all: $(TARGET)

# Build Target
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Create Object Directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Create Bin Directory
$(BINDIR):
	mkdir -p $(BINDIR)

# Compile Source Files to Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Phony Targets
.PHONY: all clean
