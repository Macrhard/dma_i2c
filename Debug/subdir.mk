################################################################################
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../init-default.c \
../init-dlm.c \
../main.c \
../utils.c 

S_UPPER_SRCS += \
../crt0.S \
../strcmp.S 

OBJS += \
./crt0.o \
./init-default.o \
./init-dlm.o \
./main.o \
./strcmp.o \
./utils.o 

C_DEPS += \
./init-default.d \
./init-dlm.d \
./main.d \
./utils.d 

S_UPPER_DEPS += \
./crt0.d \
./strcmp.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.S
	@echo '���ڹ����ļ��� $<'
	@echo '���ڵ��ã� Andes C Compiler'
	$(CROSS_COMPILE)gcc -O0 -mcmodel=medium -g3 -Wall -mcpu=d1088 -c -fmessage-length=0 -mext-dsp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $(@:%.o=%.o)" -o "$@" "$<"
	@echo '�ѽ��������� $<'
	@echo ' '

%.o: ../%.c
	@echo '���ڹ����ļ��� $<'
	@echo '���ڵ��ã� Andes C Compiler'
	$(CROSS_COMPILE)gcc -O0 -mcmodel=medium -g3 -Wall -mcpu=d1088 -c -fmessage-length=0 -mext-dsp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $(@:%.o=%.o)" -o "$@" "$<"
	@echo '�ѽ��������� $<'
	@echo ' '


