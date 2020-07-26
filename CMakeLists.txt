cmake_minimum_required(VERSION 3.0)

project(rholmes LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

option(BUILD_CURL OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(HTTP_ONLY ON)
set(BUILD_TESTING OFF)
set(BUILD_CURL_EXE OFF)
set(USE_MANUAL OFF)

file(GLOB SOURCE_FILES src/*.c)
file(GLOB HEADER_FILES src/*.h)

if(BUILD_CURL)
  add_subdirectory(lib/curl)
else()
  find_package(CURL REQUIRED)
  include_directories(${CURL_INCLUDE_DIRS})
endif()

add_executable(rholmes ${SOURCE_FILES} ${HEADER_FILES})

if(BUILD_CURL)
  target_link_libraries(rholmes libcurl)
else()
  target_link_libraries(rholmes ${CURL_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
