cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
set(FREERTOS_KERNEL_PATH "C:/FreeRTOS-Kernel")
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)


project(ATIVIDADE-12 C CXX ASM) 
pico_sdk_init()


include_directories(${CMAKE_SOURCE_DIR}/libs/include) # Adiciona o diretório 'libs/include' à lista global de diretórios de headers 

add_subdirectory(libs/FatFs_SPI) # Adiciona a biblioteca FatFs_SPI

add_executable(${PROJECT_NAME}  
        ATIVIDADE-12.c # Código principal em C
        libs/src/tasks/capturar_dados.c # Implementação da tarefa de captura de dados
        libs/src/mpu6050.c # Implementação do driver MPU6050
        libs/src/tasks/montar_desmontar.c # Implementação da tarefa de montar/desmontar o cartão SD
        libs/src/tasks/gravar_dados.c # Implementação da tarefa de gravar dados no cartão SD
        libs/src/tasks/capturar_dados.c # Header da tarefa de captura de dados
        hw_config.c # Configuração do leitor de cartão SD
        libs/src/fatfslib.c # Implementação da biblioteca FatFs
        libs/src/tasks/leds.c # Implementação da tarefa de controle dos LEDs
        libs/src/tasks/display.c # Implementação da tarefa de exibição no display
        libs/src/ssd1306.c # Implementação da biblioteca do SSD1306
        libs/src/tasks/buzzer.c # Implementação da tarefa de controle do buzzer
        )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})  # Adiciona o diretório raiz como include privado apenas para o target atual

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
    FatFs_SPI
    hardware_i2c
    hardware_clocks
    hardware_pwm
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})