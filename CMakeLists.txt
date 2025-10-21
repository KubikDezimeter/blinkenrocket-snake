cmake_minimum_required(VERSION 3.22)

project(
    BlinkenrocketBreakout
    LANGUAGES CXX
)

add_executable(Breakout
    src/main.cpp
    src/Ball.cpp
    src/Coordinates.cpp
    src/Frame.cpp
    src/Game.cpp
    src/Paddle.cpp
    src/PongGame.cpp
    src/TerminalDisplay.cpp
    src/Vector.cpp
    src/Wall.cpp
)
set_property(TARGET Breakout PROPERTY CXX_STANDARD 17)
