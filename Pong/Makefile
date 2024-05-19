Compiler := gcc
Linker := gcc
TargetFileName := program
BuildsDir := bin
SourcesDir := src

RootDir := $(shell cd)
SourcesWithFullName := $(shell dir /s /b *.c)
Sources := $(subst $(RootDir)\,,$(SourcesWithFullName))

Objects := $(patsubst %,$(BuildsDir)\\%.o,$(Sources))

AllSourcesDirs := $(shell dir $(SourcesDir) /s /b /ad)
IncludeDirs := $(addprefix -I,$(AllSourcesDirs))
CompilerFlags := $(IncludeDirs) -MMD -MP

LinkerFlags := -lntdll

DependenciesFiles := $(subst .o,.d,$(Objects))

.PHONY: all
all: $(Objects)
	$(Linker) $(Objects) -o $(BuildsDir)\$(TargetFileName) $(LinkerFlags)

$(Objects): $(BuildsDir)\\%.c.o : %.c
	if not exist $(dir $@) mkdir $(dir $@)
	$(Compiler) $(CompilerFlags) -c $< -o $@

.PHONY: allClean
allClean: clean all

.PHONY: clean
clean:
	if exist $(BuildsDir) rmdir /s /q $(BuildsDir)

-include $(DependenciesFiles)