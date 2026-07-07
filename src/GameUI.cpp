#define RAYGUI_IMPLEMENTATION
#include "../headers/GameUI.hpp"

GameUI::GameUI()
{
    for (int i = 0; i < SQUARES_COUNT; i++)
    {
        Rectangle rect {0, 0, size, size};
        Color color;

        switch (i)
        {
            case 0:
                color = BLUE;
                break;

            case 1:
                color = YELLOW;
                break;

            case 2:
                color = RED;
                break;
        }
        std::pair<Rectangle, Color> pair = {rect, color};
        squares.at(i) = pair;
    }
}

void GameUI::ChangeSelectedColor(const int& number)
{
    selectedColor = selectedColor == number ? -1 : number;
};

void GameUI::Update()
{
    AbilitiesUI();
    Input();
    SelectWithMouse();
}

void GameUI::AbilitiesUI()
{
    static const int spacing = size / 2;
    static const int totalWidth = (SQUARES_COUNT * size) + ((SQUARES_COUNT - 1) * spacing);
    
    static const float x = (GetScreenWidth() - totalWidth) / 1.1f; // DONT CHANGE THIS SHIT OR ALL OF THIS WILL BRAKE LOL
    static const float y = GetScreenHeight() - (GetScreenHeight() / 7.f);

    for (int i = 0; i < SQUARES_COUNT; i++)
    {
        float customSize = size;
        float offset_x = x - i * (customSize + spacing);

        if (i == selectedColor)
        {
            customSize *= 1.3f;
        }

        auto& rect = squares.at(i).first;
        auto color = squares.at(i).second;

        rect.x = offset_x - (customSize / 2.f);
        rect.y = y - (customSize / 2.f);
        rect.width = customSize;
        rect.height = customSize;

        GuiDrawRectangle(rect, 3, BLACK, color);
    }
}

void GameUI::Input()
{
    if (IsKeyReleased(KEY_ONE))
    {
        ChangeSelectedColor(2);
    }

    if (IsKeyReleased(KEY_TWO))
    {
        ChangeSelectedColor(1);
    }

    if (IsKeyReleased(KEY_THREE))
    {
        ChangeSelectedColor(0);
    }
}

void GameUI::SelectWithMouse()
{
    for (int i = 0; i < SQUARES_COUNT; i++)
    {
        if (IsMouseButtonReleased(0) && CheckCollisionPointRec(GetMousePosition(), squares.at(i).first))
        {
            ChangeSelectedColor(i);
        }
    }
}