Compiler := gcc
Linker := gcc
TargetFileName := program
BuildsDir := bin
SourcesDir := src
LinkerFlags := -l ntdll

Sources := $(shell find $(SourcesDir) -name '*.c')
Objects := $(patsubst %,$(BuildsDir)/%.o,$(Sources))

AllSourcesDirs := $(shell find $(SourcesDir) -type d)
IncludeDirs := $(addprefix -I,$(AllSourcesDirs))
CompilerFlags := $(IncludeDirs) -MMD -MP
DependenciesFiles := $(subst .o,.d,$(Objects))

.PHONY: all
all: $(Objects)
	$(Linker) $(Objects) -o $(BuildsDir)/$(TargetFileName) $(LinkerFlags)

$(Objects): $(BuildsDir)/%.c.o : %.c
	mkdir -p $(dir $@)
	$(Compiler) $(CompilerFlags) -c $< -o $@

.PHONY: allClean
allClean: clean all

.PHONY: clean
clean:
	rm -r $(BuildsDir)

-include $(DependenciesFiles)