cmake_minimum_required(VERSION 3.8)

project("SDL2_gfx")

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SOURCES
	SDL2_framerate.c
	SDL2_framerate.h
	SDL2_gfxPrimitives_font.h
	SDL2_gfxPrimitives.c
	SDL2_gfxPrimitives.h
	SDL2_imageFilter.c
	SDL2_imageFilter.h
	SDL2_rotozoom.c
	SDL2_rotozoom.h
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES})

include_directories(.)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})


install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	PUBLIC_HEADER DESTINATION include)



