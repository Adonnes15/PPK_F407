################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../winc1500/root_cert/X509/asn1.c \
../winc1500/root_cert/X509/hash.c \
../winc1500/root_cert/X509/x509_cert.c 

OBJS += \
./winc1500/root_cert/X509/asn1.o \
./winc1500/root_cert/X509/hash.o \
./winc1500/root_cert/X509/x509_cert.o 

C_DEPS += \
./winc1500/root_cert/X509/asn1.d \
./winc1500/root_cert/X509/hash.d \
./winc1500/root_cert/X509/x509_cert.d 


# Each subdirectory must supply rules for building sources it contributes
winc1500/root_cert/X509/%.o winc1500/root_cert/X509/%.su winc1500/root_cert/X509/%.cyclo: ../winc1500/root_cert/X509/%.c winc1500/root_cert/X509/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/config" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv/resources" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv/src" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/programmer" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/root_cert/X509" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/socket/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/socket/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/spi_flash/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/spi_flash/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bsp/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bsp/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bus_wrapper/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bus_wrapper/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/common/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/common/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/driver/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/driver/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/Drivers/BSP/STM32F4xx_Discovery_407/Inc" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/Drivers/BSP/STM32F4xx_Discovery_407/Src" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-winc1500-2f-root_cert-2f-X509

clean-winc1500-2f-root_cert-2f-X509:
	-$(RM) ./winc1500/root_cert/X509/asn1.cyclo ./winc1500/root_cert/X509/asn1.d ./winc1500/root_cert/X509/asn1.o ./winc1500/root_cert/X509/asn1.su ./winc1500/root_cert/X509/hash.cyclo ./winc1500/root_cert/X509/hash.d ./winc1500/root_cert/X509/hash.o ./winc1500/root_cert/X509/hash.su ./winc1500/root_cert/X509/x509_cert.cyclo ./winc1500/root_cert/X509/x509_cert.d ./winc1500/root_cert/X509/x509_cert.o ./winc1500/root_cert/X509/x509_cert.su

.PHONY: clean-winc1500-2f-root_cert-2f-X509

