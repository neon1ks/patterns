cmake_minimum_required(VERSION 3.5)

project(patterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SBOMBER_SOURCE
    Bomb.cpp
    Bomb.h
    DestroyableGroundObject.h
    DynamicObject.h
    GameObject.h
    Ground.cpp
    Ground.h
    House.cpp
    House.h
    LevelGUI.cpp
    LevelGUI.h
    MyTools.cpp
    MyTools.h
    Plane.cpp
    Plane.h
    SBomber.cpp
    SBomber.h
    SBomberProject.cpp
    Tank.cpp
    Tank.h
)

add_executable(patterns ${SBOMBER_SOURCE})

