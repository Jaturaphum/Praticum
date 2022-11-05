# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/opt/pico-sdk/tools/pioasm"
  "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pioasm"
  "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm"
  "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/tmp"
  "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src"
  "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jaturaphum/Downloads/0373/Praticum/PraticumII/build/pico-sdk/src/rp2_common/cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
