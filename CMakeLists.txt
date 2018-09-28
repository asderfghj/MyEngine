cmake_minimum_required(VERSION 2.6)
project (MYENGINE)

add_executable(game
	src/game/main.cpp
)

add_library(engine
	src/myengine/Core.cpp
	src/myengine/Core.h
)

