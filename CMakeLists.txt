cmake_minimum_required(VERSION 3.25)
project(golfgame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Static linking flags
add_compile_options(
    -static 
    -static-libgcc 
    -static-libstdc++ 
    -fsanitize=undefined 
    -fsanitize-undefined-trap-on-error 
)

add_link_options(
    -static 
    -fsanitize=undefined 
    -fsanitize-undefined-trap-on-error 
)

# Fetch raylib using FetchContent
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

# Fetch raygui using FetchContent (updated to match raylib)
FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG master
)

FetchContent_MakeAvailable(raygui)

# Include directories for raylib and raygui
include_directories(${raylib_SOURCE_DIR}/src)
include_directories(${raygui_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

# Add sources (do not include header files here)
set(SOURCES
    src/main.cpp
    src/program.cpp
    src/mouse.cpp
    src/menu.cpp
    src/button.cpp
    src/textureClass.cpp
    src/startMenu.cpp
    src/generalSettingsMenu.cpp
    src/multiplayerMenu.cpp
    src/joinMultiplayerMenu.cpp
    src/singleplayerGameSettingsMenu.cpp
    src/singleplayerMatch.cpp
    src/ball.cpp
    src/match.cpp
    src/terrain.cpp
    src/gameMusic.cpp
    src/userSettings.cpp
    src/singleplayerWinMenu.cpp
)

# Define headers for inclusion in source files (headers should not be added to SOURCES list)
set(HEADERS
    src/program.h
    src/ScreenSizeTransfer.h
    src/GuiEnum.h
    src/mouse.h
    src/menu.h
    src/button.h
    src/textureClass.h
    src/startMenu.h
    src/generalSettingsMenu.h
    src/multiplayerMenu.h
    src/joinMultiplayerMenu.h
    src/singleplayerGameSettingsMenu.h
    src/singleplayerMatch.h
    src/ball.h
    src/match.h
    src/terrain.h
    src/gameMusic.h
    src/userSettings.h
    src/singleplayerWinMenu.h
)

# Create the executable and link raylib and raygui
add_executable(main ${SOURCES})
target_compile_options(main PRIVATE 
    #-Wall -Wextra -pedantic -Werror
)
target_link_libraries(main raylib)

# Add custom target to copy resources (images, etc.) to build directory
add_custom_target(copyresources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
    COMMENT "Copying resources to the build directory"
)
