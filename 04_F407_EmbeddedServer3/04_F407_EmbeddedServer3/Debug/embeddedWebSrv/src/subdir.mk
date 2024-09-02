################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../embeddedWebSrv/src/GPS.c \
../embeddedWebSrv/src/LoremIpsum.c \
../embeddedWebSrv/src/helperFunctions.c \
../embeddedWebSrv/src/http_SSI_replacer.c \
../embeddedWebSrv/src/http_cgi.c \
../embeddedWebSrv/src/http_file.c \
../embeddedWebSrv/src/http_local_filesystem.c \
../embeddedWebSrv/src/http_net.c \
../embeddedWebSrv/src/http_request_parser.c \
../embeddedWebSrv/src/http_response.c \
../embeddedWebSrv/src/http_server.c \
../embeddedWebSrv/src/http_server_platform.c \
../embeddedWebSrv/src/imu.c 

OBJS += \
./embeddedWebSrv/src/GPS.o \
./embeddedWebSrv/src/LoremIpsum.o \
./embeddedWebSrv/src/helperFunctions.o \
./embeddedWebSrv/src/http_SSI_replacer.o \
./embeddedWebSrv/src/http_cgi.o \
./embeddedWebSrv/src/http_file.o \
./embeddedWebSrv/src/http_local_filesystem.o \
./embeddedWebSrv/src/http_net.o \
./embeddedWebSrv/src/http_request_parser.o \
./embeddedWebSrv/src/http_response.o \
./embeddedWebSrv/src/http_server.o \
./embeddedWebSrv/src/http_server_platform.o \
./embeddedWebSrv/src/imu.o 

C_DEPS += \
./embeddedWebSrv/src/GPS.d \
./embeddedWebSrv/src/LoremIpsum.d \
./embeddedWebSrv/src/helperFunctions.d \
./embeddedWebSrv/src/http_SSI_replacer.d \
./embeddedWebSrv/src/http_cgi.d \
./embeddedWebSrv/src/http_file.d \
./embeddedWebSrv/src/http_local_filesystem.d \
./embeddedWebSrv/src/http_net.d \
./embeddedWebSrv/src/http_request_parser.d \
./embeddedWebSrv/src/http_response.d \
./embeddedWebSrv/src/http_server.d \
./embeddedWebSrv/src/http_server_platform.d \
./embeddedWebSrv/src/imu.d 


# Each subdirectory must supply rules for building sources it contributes
embeddedWebSrv/src/%.o embeddedWebSrv/src/%.su embeddedWebSrv/src/%.cyclo: ../embeddedWebSrv/src/%.c embeddedWebSrv/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/config" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv/resources" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv/src" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/embeddedWebSrv" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/programmer" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/root_cert/X509" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/socket/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/socket/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/spi_flash/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/spi_flash/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bsp/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bsp/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bus_wrapper/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/bus_wrapper/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/common/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/common/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/driver/include" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500/driver/source" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/winc1500" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/Drivers/BSP/STM32F4xx_Discovery_407/Inc" -I"C:/Users/NinaadKotasthane/OneDrive/Documents/STM32/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/04_F407_EmbeddedServer3/Drivers/BSP/STM32F4xx_Discovery_407/Src" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-embeddedWebSrv-2f-src

clean-embeddedWebSrv-2f-src:
	-$(RM) ./embeddedWebSrv/src/GPS.cyclo ./embeddedWebSrv/src/GPS.d ./embeddedWebSrv/src/GPS.o ./embeddedWebSrv/src/GPS.su ./embeddedWebSrv/src/LoremIpsum.cyclo ./embeddedWebSrv/src/LoremIpsum.d ./embeddedWebSrv/src/LoremIpsum.o ./embeddedWebSrv/src/LoremIpsum.su ./embeddedWebSrv/src/helperFunctions.cyclo ./embeddedWebSrv/src/helperFunctions.d ./embeddedWebSrv/src/helperFunctions.o ./embeddedWebSrv/src/helperFunctions.su ./embeddedWebSrv/src/http_SSI_replacer.cyclo ./embeddedWebSrv/src/http_SSI_replacer.d ./embeddedWebSrv/src/http_SSI_replacer.o ./embeddedWebSrv/src/http_SSI_replacer.su ./embeddedWebSrv/src/http_cgi.cyclo ./embeddedWebSrv/src/http_cgi.d ./embeddedWebSrv/src/http_cgi.o ./embeddedWebSrv/src/http_cgi.su ./embeddedWebSrv/src/http_file.cyclo ./embeddedWebSrv/src/http_file.d ./embeddedWebSrv/src/http_file.o ./embeddedWebSrv/src/http_file.su ./embeddedWebSrv/src/http_local_filesystem.cyclo ./embeddedWebSrv/src/http_local_filesystem.d ./embeddedWebSrv/src/http_local_filesystem.o ./embeddedWebSrv/src/http_local_filesystem.su ./embeddedWebSrv/src/http_net.cyclo ./embeddedWebSrv/src/http_net.d ./embeddedWebSrv/src/http_net.o ./embeddedWebSrv/src/http_net.su ./embeddedWebSrv/src/http_request_parser.cyclo ./embeddedWebSrv/src/http_request_parser.d ./embeddedWebSrv/src/http_request_parser.o ./embeddedWebSrv/src/http_request_parser.su ./embeddedWebSrv/src/http_response.cyclo ./embeddedWebSrv/src/http_response.d ./embeddedWebSrv/src/http_response.o ./embeddedWebSrv/src/http_response.su ./embeddedWebSrv/src/http_server.cyclo ./embeddedWebSrv/src/http_server.d ./embeddedWebSrv/src/http_server.o ./embeddedWebSrv/src/http_server.su ./embeddedWebSrv/src/http_server_platform.cyclo ./embeddedWebSrv/src/http_server_platform.d ./embeddedWebSrv/src/http_server_platform.o ./embeddedWebSrv/src/http_server_platform.su ./embeddedWebSrv/src/imu.cyclo ./embeddedWebSrv/src/imu.d ./embeddedWebSrv/src/imu.o ./embeddedWebSrv/src/imu.su

.PHONY: clean-embeddedWebSrv-2f-src

