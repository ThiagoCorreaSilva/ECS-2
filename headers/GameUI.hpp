#pragma once

#include <raygui.h>
#include <raylib.h>

#include <array>

constexpr int squares = 3;
constexpr int size = 100;

class GameUI
{
private:
    std::array<Color, squares> colors;

public:
    GameUI();
    void abilitiesUI();
};