#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building of executables and static libraries.
#
# usage: Edit "VARIABLES"-section to suit project requirements.
#        For debug build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Debug -DCMAKE_BUILD_TYPE=Debug
#          make -C Debug VERBOSE=1
#        For release build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Release -DCMAKE_BUILD_TYPE=Release
#          make -C Release VERBOSE=1
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)

###################### CONSTANTS ######################################
set (PROJECT_TYPE_EXECUTABLE          "exe")
set (PROJECT_TYPE_STATIC_LIBRARY      "static-lib")
set (MCPU_CORTEX_M0				      "-mcpu=cortex-m0")
set (MCPU_CORTEX_M0PLUS				  "-mcpu=cortex-m0plus")
set (MCPU_CORTEX_M3				      "-mcpu=cortex-m3")
set (MCPU_CORTEX_M4				      "-mcpu=cortex-m4")
set (MCPU_CORTEX_M7				      "-mcpu=cortex-m7")
set (MCPU_CORTEX_M33				  "-mcpu=cortex-m33")
set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_STD_C            "")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (RUNTIME_LIBRARY_SYSCALLS_NONE    "")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
#######################################################################

###################### VARIABLES ######################################
set (PROJECT_NAME             "StmTextCMake")
set (PROJECT_TYPE             "exe")
set (LINKER_SCRIPT            "../STM32H735IGKX_FLASH.ld")
set (MCPU                     "-mcpu=Cortex-M7")
set (MFPU                 "-mfpu=fpv5-d16")
set (MFLOAT_ABI               "")
set (RUNTIME_LIBRARY          "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")

# set(STM32Cube_PATH $ENV{HOME}/STM32Cube/Repository/STM32Cube_FW_H7_V1.11.1)
set(STM32Cube_PATH ${CMAKE_SOURCE_DIR}/Drivers/STM32CubeH7)


set (PROJECT_SOURCES
	# LIST SOURCE FILES HERE
	Sources/main.c
	Sources/syscalls.c
	Sources/sysmem.c

	Sources/printer.cpp
  Sources/stm_slint_platform.cpp

  ${STM32Cube_PATH}/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery.c
  ${STM32Cube_PATH}/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_lcd.c
  ${STM32Cube_PATH}/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ts.c
  ${STM32Cube_PATH}/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_bus.c
  ${STM32Cube_PATH}/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_ospi.c
  #${STM32Cube_PATH}/Drivers/BSP/STM32H735G-DK/stm32h735g_discovery_sd.c
  ${STM32Cube_PATH}/Drivers/BSP/Components/ft5336/ft5336.c
  ${STM32Cube_PATH}/Drivers/BSP/Components/ft5336/ft5336_reg.c
  ${STM32Cube_PATH}/Drivers/BSP/Components/mx25lm51245g/mx25lm51245g.c
  ${STM32Cube_PATH}/Drivers/BSP/Components/s70kl1281/s70kl1281.c
  ${STM32Cube_PATH}/Projects/STM32H735G-DK/Templates_LL/STM32CubeIDE/Example/Startup/startup_stm32h735igkx.s
  ${STM32Cube_PATH}/Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ospi.c
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c


	)


set (PROJECT_DEFINES
	# LIST COMPILER DEFINITIONS HERE
  STM32H735xx
    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
  Sources
  ${STM32Cube_PATH}/Drivers/STM32H7xx_HAL_Driver/Inc/
  ${STM32Cube_PATH}/Drivers/CMSIS/Device/ST/STM32H7xx/Include/
  ${STM32Cube_PATH}/Drivers/CMSIS/Include
  ${STM32Cube_PATH}/Drivers/BSP/STM32H735G-DK/
  ${STM32Cube_PATH}/Drivers/BSP/Components/Common/
    )

############ MODIFY ACCORDING TO REQUIREMENTS) ########################

# Add the appropriate VFP settings based on your requirements
set(VFP_HARD "-mfloat-abi=hard")
set(VFP_SOFTFP "-mfloat-abi=softfp")

# Set the desired VFP option
set(MFLOAT_ABI ${VFP_HARD})

#######################################################################


set(Rust_CARGO_TARGET "thumbv7em-none-eabihf")
#set(CORROSION_NO_WARN_PARSE_TARGET_TRIPLE_FAILED ON)
set(SLINT_FEATURE_FREESTANDING ON)
set(SLINT_FEATURE_RENDERER_SOFTWARE ON)
set(BUILD_SHARED_LIBS OFF)
# otherwise it doesn't fit the flash
set(CMAKE_BUILD_TYPE MinRelSize)

include(FetchContent)
FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint
    GIT_TAG master
    SOURCE_SUBDIR api/cpp
)
FetchContent_MakeAvailable(Slint)



################## PROJECT SETUP ######################################
project(${PROJECT_NAME})
enable_language(ASM)

if (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_EXECUTABLE})
  add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_NAME:${CMAKE_PROJECT_NAME}>.hex)
elseif (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_STATIC_LIBRARY})
  add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Slint::Slint)
set_target_properties(${PROJECT_NAME} PROPERTIES SLINT_EMBED_RESOURCES "embed-for-software-renderer")
slint_target_sources(${PROJECT_NAME} ui/printerdemo.slint)
target_link_options(${PROJECT_NAME} PUBLIC -Wl,--allow-multiple-definition)


add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror")
set (CMAKE_CXX_FLAGS "${MCPU} ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror")
set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=test.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
