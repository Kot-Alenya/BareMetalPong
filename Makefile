Compiler := i386-elf-gcc
Linker := i386-elf-gcc
TargetFileName := program
BuildsDir := bin
SourcesDir := src
LinkerFlags := -T linker.ld -ffreestanding -O3 -nostdlib -lgcc
Grub := grub-mkrescue
GrubConfig := grub.cfg
GrubStartDirName := isodir
GrubFlags := --compress=xz --iso-level 2

Sources := $(shell find $(SourcesDir) -name '*.c' -or -name '*.asm')
Objects := $(patsubst %,$(BuildsDir)/%.o,$(Sources))
AllSourcesDirs := $(shell find $(SourcesDir) -type d)
IncludeDirs := $(addprefix -I,$(AllSourcesDirs))

CCompilerFlagsRelease := -MMD -MP -std=gnu99 -ffreestanding -O3 -Wall -Wextra $(IncludeDirs)
CCompilerFlagsDebug := -MMD -MP -std=gnu99 -ffreestanding -O0 -Wall -Wextra -g $(IncludeDirs)

AsmCompilerFlagsRelease := -felf $(IncludeDirs)
AsmCompilerFlagsDebug := -felf -g $(IncludeDirs)

DependenciesFiles := $(subst .o,.d,$(Objects))
GrubAdditionBinDir := $(BuildsDir)/$(GrubStartDirName)/boot/
GrubAdditionConfigDir := $(BuildsDir)/$(GrubStartDirName)/boot/grub

CCompilerFlags := $(CCompilerFlagsDebug)
AsmCompilerFlags := $(AsmCompilerFlagsDebug)

ifneq ($(filter -release, $(MAKECMDGOALS)),)
	CCompilerFlags := $(CCompilerFlagsRelease)
	AsmCompilerFlags := $(AsmCompilerFlagsRelease)
endif

.PHONY: all
all: $(BuildsDir)/$(TargetFileName).iso

$(BuildsDir)/$(TargetFileName).iso: $(GrubAdditionConfigDir)/$(GrubConfig) $(GrubAdditionBinDir)/$(TargetFileName).bin
	cd $(BuildsDir) && $(Grub) -o $(TargetFileName).iso $(GrubStartDirName) $(GrubFlags)

$(GrubAdditionConfigDir)/$(GrubConfig): $(GrubConfig)
	mkdir -p $(GrubAdditionConfigDir)
	cp $(GrubConfig) $(GrubAdditionConfigDir)

$(GrubAdditionBinDir)/$(TargetFileName).bin: $(BuildsDir)/$(TargetFileName).bin
	cp $(BuildsDir)/$(TargetFileName).bin $(GrubAdditionBinDir)

$(BuildsDir)/$(TargetFileName).bin: $(Objects)
	@echo
	$(Linker) $(Objects) -o $(BuildsDir)/$(TargetFileName).bin $(LinkerFlags)

define MakeObjectDirMacro
	@echo
	mkdir -p $(dir $@)
endef

$(BuildsDir)/%.c.o : %.c
	$(call MakeObjectDirMacro)
	$(Compiler) -c $< -o $@ $(CCompilerFlags)

$(BuildsDir)/%.s.o : %.s
	$(call MakeObjectDirMacro)
	$(Compiler) -c $< -o $@ $(CCompilerFlags)

$(BuildsDir)/%.asm.o : %.asm
	$(call MakeObjectDirMacro)
	nasm $< -o $@ $(AsmCompilerFlags)

.PHONY: allClean
allClean: clean all

.PHONY: clean
clean:
	rm -rf $(BuildsDir)

-include $(DependenciesFiles)