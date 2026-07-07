#define RAYGUI_IMPLEMENTATION
#include "../headers/GameUI.hpp"

GameUI::GameUI()
{
    colors.at(0) = BLUE;
    colors.at(1) = RED;
    colors.at(2) = YELLOW;
}

void GameUI::abilitiesUI()
{
    static const int spacing = size / 2;
    static const int totalWidth = (squares * size) + ((squares - 1) * spacing);
    
    static const float x = (GetScreenWidth() - totalWidth) / 1.2f;
    static const float y = GetScreenHeight() - (GetScreenHeight() / 5.f);

    for (int i = 0; i < squares; i++)
    {
        float offset_x = x - i * (size + spacing);
        Rectangle rect {offset_x, y, size, size};

        GuiDrawRectangle(rect, 3, BLACK, colors.at(i));
    }
}