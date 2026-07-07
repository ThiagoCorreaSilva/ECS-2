#pragma once

#include <raygui.h>
#include <raylib.h>

#include <array>
#include <iostream>

constexpr int squares = 3;

class GameUI
{
private:
    std::array<Color, squares> colors;
    float size = 100;
    int selectedColor = -1;

public:
    GameUI();

    void Update();
    void Input();
    void AbilitiesUI();
};