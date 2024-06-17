cmake_minimum_required(VERSION 3.28)
project(ZOOProjekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZOOProjekt main.cpp
        Game.cpp
        Dungeon.cpp
        Inventory.cpp
        Character.cpp
        Armor.cpp
        Hero.cpp
        Item.cpp
        Monster.cpp
        Potion.cpp
        Sword.cpp)