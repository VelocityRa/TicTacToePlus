cmake_minimum_required(VERSION 2.6)
project(TicTacToe)

# Enable debug symbols by default
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Define sources and executable
set(TicTacToe_SOURCES TTTBoard.cpp TTTScoreboard.cpp main.cpp)
set(TicTacToe_NAME "TicTacToe")
add_executable(${TicTacToe_NAME} ${TicTacToe_SOURCES})

# Force the compiler to use the C++11 standard
set_property(TARGET ${TicTacToe_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${TicTacToe_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${TicTacToe_NAME} ${SFML_LIBRARIES})
endif()
