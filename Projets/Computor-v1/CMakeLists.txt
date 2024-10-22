cmake_minimum_required(VERSION 3.8)

project("computorv1")

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB ALL_SRCS
	"${PROJECT_SOURCE_DIR}/sources/*.cpp"
)

include_directories(
	${PROJECT_SOURCE_DIR}/includes
	${PROJECT_SOURCE_DIR}/sources
)

add_executable(${PROJECT_NAME} ${ALL_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE m)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)



