#pragma once

#include <raygui.h>
#include <raylib.h>

#include <array>
#include <utility>
#include <iostream>

constexpr int SQUARES_COUNT = 3;
constexpr int DEFAULT_COLOR_1 = -1;
constexpr int DEFAULT_COLOR_2 = -2;

class GameUI
{
private:
    inline static std::array<std::pair<Rectangle, Color>, SQUARES_COUNT> squares; 
    
    inline static float size = 100;
    
    inline static int selectedColor = -1;
    inline static int selectedColor2 = -2;

    inline static bool setuped = false;

private:
    GameUI() = default;
    static void ChangeSelectedColor(const int& number);

public:
    static void Setup();
    static void Update();
    static void AbilitiesUI();
    static void Input();
    static void SelectWithMouse();
    static bool CanUsePower();
};