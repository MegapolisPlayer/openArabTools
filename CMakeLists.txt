#
# OpenArabTools CMake List
# (c) Martin/MegapolisPlayer and contributors, 2024
#

cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD, 11)
set(CMAKE_C_STANDARD_REQUIRED, TRUE)
set(CMAKE_CXX_STANDARD, 20)
set(CMAKE_CXX_STANDARD_REQUIRED, TRUE)

# openArabTools

project(openArabTools VERSION 0.1.0)
add_compile_definitions(OPENARABTOOLS_BUILD_DLL)
add_compile_definitions(GLEW_NO_GLU)
add_library(openArabTools SHARED
"openArabTools/include/OpenArabTools.hpp"
"openArabTools/include/OpenArabTools.cpp"
"openArabTools/src/StandardInclude.hpp"
"openArabTools/src/Utils.hpp"
"openArabTools/src/Error.hpp"
"openArabTools/src/Utils.cpp"
"openArabTools/src/Error.cpp"
"openArabTools/src/event/Event.hpp"
"openArabTools/src/event/Event.cpp"
"openArabTools/src/remote/Client.hpp"
"openArabTools/src/remote/Client.cpp"
"openArabTools/src/remote/Server.hpp"
"openArabTools/src/remote/Server.cpp"
"openArabTools/src/remote/Remote.hpp"
"openArabTools/src/types/LightColor.hpp"
"openArabTools/src/types/LightColor.cpp"
"openArabTools/src/graphics/internal/GLBaseImplementation.hpp"
"openArabTools/src/graphics/internal/GLBaseImplementation.cpp"
"openArabTools/src/graphics/internal/GLWindow.hpp"
"openArabTools/src/graphics/internal/GLWindow.cpp"
"openArabTools/src/graphics/internal/GLInterface.hpp"
"openArabTools/src/graphics/Matrix.hpp"
"openArabTools/src/graphics/Matrix.cpp"
"openArabTools/src/graphics/Canvas.hpp"
"openArabTools/src/graphics/Canvas.cpp"
"openArabTools/src/graphics/Chessboard.hpp"
"openArabTools/src/graphics/Chessboard.cpp"
"openArabTools/src/graphics/Crossing.hpp"
"openArabTools/src/graphics/Crossing.cpp"
"openArabTools/src/graphics/Dice.hpp"
"openArabTools/src/graphics/Dice.cpp"
"openArabTools/src/graphics/Semaphore.hpp"
"openArabTools/src/graphics/Semaphore.cpp"
"openArabTools/src/graphics/Graphics.hpp"
)
target_include_directories(openArabTools PUBLIC
"depend/glew/include/"
"depend/glfw/include/"
)
target_link_directories(openArabTools PUBLIC
"depend/glew/"
"depend/glfw/"
)
target_link_libraries(openArabTools PUBLIC -lGL -lglfw -lGLEW)

# exampleProj

project(exampleProj VERSION 0.1.0)
add_compile_definitions(GLEW_NO_GLU)
add_executable(exampleProj
"exampleProj/Main.cpp"
)
target_include_directories(exampleProj PUBLIC
"openArabTools/include/"
"depend/glew/include/"
"depend/glfw/include/"
)
target_link_directories(exampleProj PUBLIC
"."
"depend/glew/"
"depend/glfw/"
)
target_link_libraries(exampleProj PUBLIC openArabTools -lGL -lglfw -lGLEW)


