# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/carolina/Documentos/embebidos/TPP/esp-idf/components/bootloader/subproject"
  "/home/carolina/Documentos/embebidos/TPP/esp-idf/projects/VRGlove/build/bootloader"
  "/home/carolina/Documentos/embebidos/TPP/esp-idf/projects/VRGlove/build/bootloader-prefix"
  "/home/carolina/Documentos/embebidos/TPP/esp-idf/projects/VRGlove/build/bootloader-prefix/tmp"
  "/home/carolina/Documentos/embebidos/TPP/esp-idf/projects/VRGlove/build/bootloader-prefix/src/bootloader-stamp"
  "/home/carolina/Documentos/embebidos/TPP/esp-idf/projects/VRGlove/build/bootloader-prefix/src"
  "/home/carolina/Documentos/embebidos/TPP/esp-idf/projects/VRGlove/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/carolina/Documentos/embebidos/TPP/esp-idf/projects/VRGlove/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
