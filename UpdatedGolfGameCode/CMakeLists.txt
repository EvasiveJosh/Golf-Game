cmake_minimum_required(VERSION 3.25)
project(guifinal)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add sources and headers
set(SOURCES
    program.cpp
    mouse.cpp
    menu.cpp
    button.cpp
    textureClass.cpp
    startMenu.cpp
    generalSettingsMenu.cpp
    multiplayerMenu.cpp
    joinMultiplayerMenu.cpp
    singleplayerGameSettingsMenu.cpp
    singleplayerMatch.cpp
    ball.cpp
    match.cpp
)

set(HEADERS
    program.h
    ScreenSizeTransfer.h
    GuiEnum.h
    mouse.h
    menu.h
    button.h
    textureClass.h
    startMenu.h
    generalSettingsMenu.h
    multiplayerMenu.h
    joinMultiplayerMenu.h
    singleplayerGameSettingsMenu.h
    singleplayerMatch.h
    ball.h
    match.h
)

# FetchContent to download raylib if not available
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0  # Replace with the desired raylib version
)

FetchContent_MakeAvailable(raylib)

# Create the executable and link raylib
add_executable(main main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(main raylib)