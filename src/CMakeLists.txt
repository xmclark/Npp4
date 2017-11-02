# This file is part of the Npp4 plugin for Notepad++.

# MIT License

# Copyright (c) [2017] [mackenzie clark]

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

if (MSVC) 
  foreach(flag_var
          CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
          CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
  endforeach(flag_var)
endif(MSVC)

# suppress CRT_SECURE_NO_WARNINGS
# if (MSVC)
#   add_definitions(-D_SECURE_NO_WARNINGS)
# endif(MSVC)

# section: source files
set(Npp4_SOURCE_FILES
  ./Npp4.cpp
  ./PluginDefinition.cpp)

# section: header files
set(Npp4_HEADER_FILES
  ./menuCmdID.h
  ./Notepad_plus_msgs.h
  ./json.hpp
  ./PluginDefinition.h
  ./PluginInterface.h
  # ./Resource.h
  ./Scintilla.h
  )

# set the current directory as an include directory
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})

set_source_files_properties(Npp4_HEADER_FILES
  PROPERTIES HEADER_FILE_ONLY TRUE)
list(APPEND Npp4_SOURCE_FILES ${Npp4_HEADER_FILES})

# configure_file(
#   ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
#   ${CMAKE_CURRENT_BINARY_DIR}/version.rc
#   @ONLY)

# add unicode targets

# link_directories("")

add_library(Npp4_unicode SHARED
  ${Npp4_SOURCE_FILES}
 # ${CMAKE_CURRENT_BINARY_DIR}/version.rc
  )

set_target_properties(Npp4_unicode PROPERTIES
  OUTPUT_NAME Npp4
  COMPILE_DEFINITIONS UNICODE
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/unicode
  ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/unicode
  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/unicode)

target_link_libraries(Npp4_unicode Shlwapi)
# target_link_libraries(Npp4_unicode pcre)
target_link_libraries(Npp4_unicode ws2_32) 

add_custom_command(TARGET Npp4_unicode POST_BUILD 
COMMAND "${CMAKE_COMMAND}" -E copy 
   "$<TARGET_FILE:Npp4_unicode>"
   "${PROJECT_BINARY_DIR}/bin/unicode/$<CONFIGURATION>/Plugins/$<TARGET_FILE_NAME:Npp4_unicode>" 
COMMENT "Copying to output directory")

add_custom_command(TARGET Npp4_unicode POST_BUILD 
COMMAND "${CMAKE_COMMAND}" -E copy 
   "$<TARGET_PDB_FILE:Npp4_unicode>"
   "${PROJECT_BINARY_DIR}/bin/unicode/$<CONFIGURATION>/Plugins/$<TARGET_PDB_FILE_NAME:Npp4_unicode>" 
COMMENT "Copying to output directory")