CROSS_COMPILE ?=
CXX ?= $(CROSS_COMPILE)g++
CC ?= $(CROSS_COMPILE)gcc
UIC = uic
LDFLAGS +=-Wl,--gc-sections
CXXFLAGS = -fPIC -std=c++20
LIBS = 


SRCDIR = src
OBJDIR = build
OUTPUT = emu
RELEASEDIR = bin
RELEASE = $(addprefix $(RELEASEDIR)/, $(OUTPUT))
OBJECTS = main.o cpu.o registers.o ram.o
HEADERS = 
OBJS += $(addprefix $(OBJDIR)/, $(OBJECTS))

all: $(OUTPUT)

$(RELEASE): $(OUTPUT)

run: $(RELEASE)
	@echo [Executing $<]
	$<

$(OUTPUT): | $(OBJS)
	@echo [Linking $@]
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(RELEASE) $(LIBS) -Wl,-Map,$(OUTPUT).map


$(OBJS): | $(OBJDIR) $(HEADERS) $(RELEASEDIR)

$(RELEASEDIR) $(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo [Compiling $<]
	$(CXX) -c $(CXXFLAGS) -o $@ $< 

.PHONY: clean
clean:
	rm -rfv $(OBJDIR) $(OUTPUT) $(OUTPUT).gdb $(OUTPUT).map $(HEADERS) $(RELEASEDIR)

%.h: %.ui
	@echo [Compiling $<]
	$(UIC) -o $@ $<
