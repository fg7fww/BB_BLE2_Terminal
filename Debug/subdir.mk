################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app.c 

OBJS += \
./app.o 

C_DEPS += \
./app.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -Wall -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DRSL10_CID=101 -DCFG_BLE=1 -DCFG_ALLROLES=1 -DCFG_APP -DCFG_APP_BATT -DCFG_ATTS=1 -DCFG_CON=1 -DCFG_EMB=1 -DCFG_HOST=1 -DCFG_RF_ATLAS=1 -DCFG_ALLPRF=1 -DCFG_PRF=1 -DCFG_NB_PRF=2 -DCFG_CHNL_ASSESS=1 -DCFG_SEC_CON=1 -DCFG_EXT_DB -DCFG_PRF_BASS=1 -I"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//include" -I"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//include/bb" -I"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//include/ble" -I"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//include/kernel" -I"C:/Users/fg7fww/_Install/App/DemoBoards/RSL10/Packages_RSL10_2.0/ONSemiconductor/RSL10/2.0.0//include/ble/profiles" -I"C:\Users\fg7fww\_Install\App\DemoBoards\RSL10\workspace_r2.0_2\BB_BLE2_Terminal\code" -I"C:\Users\fg7fww\_Install\App\DemoBoards\RSL10\workspace_r2.0_2\BB_BLE2_Terminal\include" -std=gnu11 -Wmissing-prototypes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


