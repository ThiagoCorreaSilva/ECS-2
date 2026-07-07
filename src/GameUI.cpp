#define RAYGUI_IMPLEMENTATION
#include "../headers/GameUI.hpp"

GameUI::GameUI()
{
    colors.at(0) = BLUE;
    colors.at(1) = RED;
    colors.at(2) = YELLOW;
}

void GameUI::Update()
{
    AbilitiesUI();
    Input();
}

void GameUI::AbilitiesUI()
{
    static const int spacing = size / 2;
    static const int totalWidth = (squares * size) + ((squares - 1) * spacing);
    
    static const float x = (GetScreenWidth() - totalWidth) / 1.1f; // DONT CHANGE THIS SHIT OR ALL OF THIS WILL BRAKE LOL
    static const float y = GetScreenHeight() - (GetScreenHeight() / 7.f);

    for (int i = 0; i < squares; i++)
    {
        float customSize = size;
        float offset_x = x - i * (customSize + spacing);

        if (i == selectedColor)
        {
            customSize *= 1.3f;
        }

        Rectangle rect {offset_x - (customSize / 2.f), y - (customSize / 2.f), customSize, customSize};

        GuiDrawRectangle(rect, 3, BLACK, colors.at(i));
    }
}

void GameUI::Input()
{
    if (IsKeyReleased(KEY_ONE))
    {
        selectedColor = selectedColor == 2 ? -1 : 2;
    }

    if (IsKeyReleased(KEY_TWO))
    {
        selectedColor = selectedColor == 1 ? -1 : 1;
    }

    if (IsKeyReleased(KEY_THREE))
    {
        selectedColor = selectedColor == 0 ? -1 : 0;
    }
}