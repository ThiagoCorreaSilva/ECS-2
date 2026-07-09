#include "raylib.h"
#include <unordered_map>
#include <array>
#include <string>

class Shot{
private:
    const int dotQuantit = 100;
    const float dotRadius = 3.4f;
    const Color dotColor = GRAY;
    const float arcHeight = 100;

    float YPositionCalculator(float t, float arcHeight) {
        return arcHeight * 4.0f * t * (1.0f - t);
    }

    void TrailDraw(Vector2 &playerPos){
        int mousePosX = GetMouseX();
        int mousePosY = GetMouseY();
        for (int i = 0; i < dotQuantit; ++i){
            float interval = (float)(i+1)/dotQuantit;
            float xCalcRelativePos = (mousePosX - playerPos.x) * interval + playerPos.x;
            
            float linearY = (mousePosY - playerPos.y) * interval + playerPos.y;
            float arc = YPositionCalculator(interval, arcHeight);

            float yCalcRelativePos = linearY - arc;
            DrawCircle(xCalcRelativePos,yCalcRelativePos,dotRadius,dotColor);
        }
    }

public:
    enum ShotElements{
        WATER = 0,
        RAY = 1,
        FIRE = 2
    };
    enum ShotHabilities{
        STEAM,
        PLASMA,
        STORM
    };
    ShotHabilities actualHability;
    struct Array2DHash {
        std::size_t operator()(const std::array<int, 2>& arr) const {
            // Um multiplicador primo ajuda a evitar colisões simples na tabela hash
            return std::hash<int>()(arr[0]) ^ (std::hash<int>()(arr[1]) << 1);
        }
    };

    std::unordered_map<std::array<int, 2>, ShotHabilities,Array2DHash> habilityList = {
        {{(int) WATER, (int) FIRE}, STEAM},
        {{(int) RAY, (int) FIRE}, PLASMA},
        {{(int) WATER, (int) RAY}, STORM}
    };

    void CheckChoice(std::array<int,2> *elementsSelect){
        auto checker = habilityList.find(*elementsSelect);
        if (checker != habilityList.end()){
            actualHability = habilityList[*elementsSelect];
        } else {
            auto arrayGetter = *elementsSelect;
            std::array<int, 2> newArray = {arrayGetter[1], arrayGetter[0]};
            actualHability = habilityList[newArray];
        }
    }

    void DoShot(Vector2 playerPos){
        TrailDraw(playerPos);
    }
};