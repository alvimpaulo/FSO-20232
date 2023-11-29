include(CMakePrintHelpers)

cmake_minimum_required(VERSION 3.16.3)
project(TrabSO VERSION 2 LANGUAGES CXX)
include(CMakePrintHelpers)
INCLUDE(FindPkgConfig)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")   # binary destination

file(GLOB_RECURSE SRC_DIR LIST_DIRECTORIES true "${PROJECT_SOURCE_DIR}/src/*")
list(FILTER SRC_DIR EXCLUDE REGEX ^.+\.cpp$)
list(FILTER SRC_DIR EXCLUDE REGEX ^.+\.c$)
string(APPEND SRC_DIR ";${PROJECT_SOURCE_DIR}/src")

message(SRC_DIR="${SRC_DIR}"\n\n)

file(GLOB_RECURSE HEADER_DIR LIST_DIRECTORIES true "${PROJECT_SOURCE_DIR}/include/*")
list(FILTER HEADER_DIR EXCLUDE REGEX ^.+\.hpp$)
list(FILTER HEADER_DIR EXCLUDE REGEX ^.+\.h$)
string(APPEND HEADER_DIR ";${PROJECT_SOURCE_DIR}/include")

message(HEADER_DIR="${HEADER_DIR}"\n\n)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)
message(SRC_FILES="${SRC_FILES}"\n\n)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include/*.hpp)
message(HEADER_FILES="${HEADER_FILES}"\n\n)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
  # target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunreachable-code -pedantic -Wfloat-equal -ggdb -Og -DDEBUG)
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wno-unused-parameter -Wunreachable-code -pedantic -Wfloat-equal -Wconversion -ggdb -O0 -DDEBUG")
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_THREAD_SAFE")
endif()

# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#     target_compile_options( vector-test PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
# endif()
# if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
#     target_compile_options( vector-test PRIVATE /W3 /w44265 /w44061 /w44062 )
# endif()

if(MINGW)
  # list(APPEND CMAKE_CXX_FLAGS_DEBUG "-mconsole")
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -mconsole")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
endif()

ADD_LIBRARY(${PROJECT_NAME} 
    ${SRC_FILES}
    ${HEADER_FILES}
)
target_include_directories(${PROJECT_NAME} PUBLIC  "${HEADER_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC)

# Executable
add_executable(trab src/main.cpp)

target_include_directories(trab PUBLIC "${HEADER_DIR}")
target_link_libraries(trab  PUBLIC ${PROJECT_NAME})


cmake_print_properties(TARGETS ${PROJECT_NAME} PROPERTIES INCLUDE_DIRECTORIES)
