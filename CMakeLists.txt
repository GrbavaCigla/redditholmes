cmake_minimum_required(VERSION 3.0)

project(rholmes LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

file(GLOB SOURCE_FILES src/*.c)
file(GLOB HEADER_FILES src/*.h)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

add_executable(rholmes ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(rholmes ${CURL_LIBRARIES})