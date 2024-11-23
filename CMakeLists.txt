cmake_minimum_required(VERSION 3.25)
project(golfgame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add sources and headers
#[[
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
    src/singleplayerPauseMenu.cpp
    src/hostMultiplayerMenu.cpp
    src/lobby.cpp
)

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
    src/raygui.h
    src/gameMusic.h
    src/userSettings.h
    src/singleplayerWinMenu.h
    src/singleplayerPauseMenu.h
    src/hostMultiplayerMenu.h
    src/lobby.h
)
]]

set(SOURCES src/rectangle.cpp)

file(GLOB HEADERS "src/*.h")
file(GLOB SOURCES "src/*.cpp")

add_compile_options(
    -static 
    -static-libgcc 
    -static-libstdc++ 
    #Forces the program to crash if undefined behavior occurs (to be removed during release build)
    -fsanitize=undefined 
    -fsanitize-undefined-trap-on-error 
    )
add_link_options(
    -static 
    #Forces the program to crash if undefined behavior occurs (to be removed during release build)
    -fsanitize=undefined 
    -fsanitize-undefined-trap-on-error 
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
add_executable(main ${SOURCES} ${HEADERS})
target_compile_options(main PRIVATE 
    #-Wall   #Turns on all warnings
    #-Wextra  #Turns on more warnings
    #-pedantic #Checks if the code is standard compliant (we're cooked)
    #-Werror #Forces all warnings to be treated as errors
    #-Wno-unused-variable #compiler does not treat unused variables as errors
    #-Wno-unused-parameter #compiler does not treat unused function variable parameters as errors
    #-Wno-sign-compare #compiler does not treat improper comparisons as errors
    -Wno-enum-compare #compiler does not treat improper enum comparisons as errors
    )
target_link_libraries(main raylib)

add_custom_target(copyresources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
    COMMENT "Copying resources to the build directory" #folder that has the images
)