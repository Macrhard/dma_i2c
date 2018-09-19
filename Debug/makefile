################################################################################
# 自动生成的文件。不要编辑！
################################################################################

ifndef ANDESIGHT_ROOT
ANDESIGHT_ROOT=/cygdrive/D/Andestech/AndeSight300STD
endif

ifndef CROSS_COMPILE
CROSS_COMPILE=nds32le-elf-
endif

ifndef SECONDARY_OUTPUT_PATH
SECONDARY_OUTPUT_PATH=output
endif

$(shell mkdir -p $(SECONDARY_OUTPUT_PATH))

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
BUILD_ARTIFACT_FILE_BASE_NAME = dma_i2c

LINKER_OUTPUTS = dma_i2c.adx

GCOV_OUT += \
$(foreach subdir,$(SUBDIRS),$(wildcard $(subdir)/*.gcda) $(wildcard $(subdir)/*.gcno)) \

GPROF_OUT += \
../gmon.sum ../gmon.out \

SYMBOL_OUTPUTS += \
$(SECONDARY_OUTPUT_PATH)/symbol.txt \

READELF_OUTPUTS += \
$(SECONDARY_OUTPUT_PATH)/readelf.txt \

SIZE_OUTPUTS += \
$(SECONDARY_OUTPUT_PATH)/.PHONY.size \

LDSAG_OUT = $(SECONDARY_OUTPUT_PATH)/nds32.ld

# 所有目标
all: dma_i2c.adx secondary-outputs

# 工具调用
dma_i2c.adx: $(OBJS) $(USER_OBJS) $(LDSAG_OUT)
	@echo '正在构建目标： $@'
	@echo '正在调用： Andes C Linker'
	$(CROSS_COMPILE)gcc -O0 -nostartfiles -static -mcmodel=medium -T"$(LDSAG_OUT)" -mvh -mext-dsp -ldsp -o "dma_i2c.adx" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo '已结束构建目标： $@'
	@echo ' '

$(foreach subdir,$(SUBDIRS),$(wildcard $(subdir)/*.gcda) $(wildcard $(subdir)/*.gcno)): dma_i2c.adx $(OBJS) $(USER_OBJS) $(LDSAG_OUT)
../gmon.sum ../gmon.out: dma_i2c.adx $(OBJS) $(USER_OBJS) $(LDSAG_OUT)

$(SECONDARY_OUTPUT_PATH)/symbol.txt: $(LINKER_OUTPUTS)
	@echo '正在调用： NM (symbol listing)'
	$(CROSS_COMPILE)nm -n -l -C "dma_i2c.adx" > $(SECONDARY_OUTPUT_PATH)/symbol.txt
	@echo '已结束构建： $@'
	@echo ' '

$(SECONDARY_OUTPUT_PATH)/readelf.txt: $(LINKER_OUTPUTS)
	@echo '正在调用： Readelf (ELF info listing)'
	$(CROSS_COMPILE)readelf -a "dma_i2c.adx" > $(SECONDARY_OUTPUT_PATH)/readelf.txt
	@echo '已结束构建： $@'
	@echo ' '

: $(LINKER_OUTPUTS)
	@echo '正在调用： Objdump (disassembly)'
	$(CROSS_COMPILE)objdump -x -d -C "dma_i2c.adx" >
	@echo '已结束构建： $@'
	@echo ' '

$(SECONDARY_OUTPUT_PATH)/.PHONY.size: $(LINKER_OUTPUTS)
	@echo '正在调用： Size (section size listing)'
	$(CROSS_COMPILE)size  "dma_i2c.adx" | tee $(SECONDARY_OUTPUT_PATH)/.PHONY.size
	@echo '已结束构建： $@'
	@echo ' '

$(SECONDARY_OUTPUT_PATH)/nds32.ld: $(SAG_SRCS)
	@echo '正在调用： LdSaG Tool'
	$(ANDESIGHT_ROOT)/utils/nds_ldsag -t $(ANDESIGHT_ROOT)/utils/nds32_template.txt $(SAG_SRCS) -o $(LDSAG_OUT)
	@echo '已结束构建： $@'
	@echo ' '

# 其他目标
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(GCOV_OUT)$(LDSAG_OUT)$(SYMBOL_OUTPUTS)$(READELF_OUTPUTS)$(GPROF_OUT)$(SIZE_OUTPUTS)$(EXECUTABLES)$(S_UPPER_DEPS) dma_i2c.adx
	-@echo ' '

secondary-outputs: $(SYMBOL_OUTPUTS) $(READELF_OUTPUTS) $(SIZE_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:
.NOTPARALLEL: pre-build

-include ../makefile.targets
