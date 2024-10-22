# ==================================================================================================
# Global configuration
# ==================================================================================================
cmake_minimum_required(VERSION 3.8)

project("server")

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB SOURCES
	"src/*.cpp"
	"src/*.hpp"
	"src/Network/*.cpp"
	"src/Network/*.hpp"
	"src/Game/*.cpp"
	"src/Game/*.hpp"
	"src/Commands/*.cpp"
	"src/Commands/*.hpp"
)

include_directories(src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -g)

target_link_libraries(${PROJECT_NAME} PRIVATE common)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Common/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include)
