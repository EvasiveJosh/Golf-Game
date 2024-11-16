cmake_minimum_required(VERSION 3.25)
project(guifinal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_executable(main main.cpp ${SOURCES} ${HEADERS}) 
target_link_libraries(main raylib)