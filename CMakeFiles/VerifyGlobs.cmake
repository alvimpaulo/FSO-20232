# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.27
cmake_policy(SET CMP0009 NEW)

# HEADER_FILES at CMakeLists.txt:32 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/paulo/unb/FSO-2/trab/include/*.hpp")
set(OLD_GLOB
  "/home/paulo/unb/FSO-2/trab/include/Processo.hpp"
  "/home/paulo/unb/FSO-2/trab/include/ProcessoManager.hpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/paulo/unb/FSO-2/trab/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES at CMakeLists.txt:29 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/paulo/unb/FSO-2/trab/src/*.cpp")
set(OLD_GLOB
  "/home/paulo/unb/FSO-2/trab/src/Processo.cpp"
  "/home/paulo/unb/FSO-2/trab/src/ProcessoManager.cpp"
  "/home/paulo/unb/FSO-2/trab/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/paulo/unb/FSO-2/trab/CMakeFiles/cmake.verify_globs")
endif()
