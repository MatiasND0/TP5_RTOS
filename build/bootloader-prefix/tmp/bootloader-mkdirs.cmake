# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/matiasnd/esp/esp-idf/components/bootloader/subproject"
  "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader"
  "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader-prefix"
  "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader-prefix/tmp"
  "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader-prefix/src/bootloader-stamp"
  "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader-prefix/src"
  "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/matiasnd/esp-workspace/Esp32_rtos/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
