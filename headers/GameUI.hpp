#pragma once

#include <raygui.h>
#include <raylib.h>

#include <array>
#include <utility>
#include <iostream>

constexpr int SQUARES_COUNT = 3;

class GameUI
{
private:
    std::array<std::pair<Rectangle, Color>, SQUARES_COUNT> squares; 
    
    float size = 100;
    int selectedColor = -1;

private:
    void ChangeSelectedColor(const int& number);

public:
    GameUI();

    void Update();
    void AbilitiesUI();
    void Input();
    void SelectWithMouse();
};