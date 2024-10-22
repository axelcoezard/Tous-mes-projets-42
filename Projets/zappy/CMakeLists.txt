# ==================================================================================================
# Global configuration
# ==================================================================================================
cmake_minimum_required(VERSION 3.8)

project("zappy")

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# ==================================================================================================
# Dependencies
# ==================================================================================================
add_subdirectory("ThirdParty/SDL")
add_subdirectory("ThirdParty/SDL_image")
add_subdirectory("ThirdParty/SDL_ttf")
add_subdirectory("ThirdParty/SDL_gfx")

# ==================================================================================================
# Modules
# ==================================================================================================
add_subdirectory("Sources/Common")
add_subdirectory("Sources/Server")
add_subdirectory("Sources/Client")
add_subdirectory("Sources/GraphicClient")
