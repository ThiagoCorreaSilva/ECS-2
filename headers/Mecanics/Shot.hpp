#include "raylib.h"
#include <unordered_map>
#include <array>
#include <string>

class Shot{
public:
    enum ShotElements{
        WATER = 0,
        RAY = 1,
        FIRE = 2
    };
    enum ShotHabilities{
        NONE = -1,
        STEAM = 0,
        PLASMA = 1,
        STORM = 2
    };
    ShotHabilities actualHability = ShotHabilities::PLASMA;

private:
    static const int dotQuantit = 50;
    const float dotRadius = 3.4f;
    const Color dotColor = GRAY;
    const float arcHeight = 100;

    //Positions importants
    Vector2 saveMousePosition;
    Vector2 bulletPosition;

    float currentFrame = 0.f;

    enum States{
        AIMING,
        SHOOTING,
        HITTING
    };
    States actualState = States::AIMING;

    struct Array2DHash {
        std::size_t operator()(const std::array<int, 2>& arr) const {
            // Um multiplicador primo ajuda a evitar colisões simples na tabela hash
            return std::hash<int>()(arr[0]) ^ (std::hash<int>()(arr[1]) << 1);
        }
    };

    void ChangeState(States newState){
        std::cout << "New state : " << newState << '\n';
        if (actualState != newState){
            actualState = newState;
        }
    }

    float YPositionCalculator(float t, float arcHeight) {
        return arcHeight * 4.0f * t * (1.0f - t);
    }

    Vector2 CalculateParabolaPoint(Vector2 startPos, Vector2 targetPos, int index, int denominator = dotQuantit) {
        float interval = (float)(index + 1) / denominator;
        float xCalcRelativePos = (targetPos.x - startPos.x) * interval + startPos.x;
        
        float linearY = (targetPos.y - startPos.y) * interval + startPos.y;
        float arc = YPositionCalculator(interval, arcHeight);
        float yCalcRelativePos = linearY - arc;

        return Vector2{xCalcRelativePos, yCalcRelativePos};
    }

    void TrailUpdate(){
        Vector2 mousePos = {(float)GetMouseX(),(float)GetMouseY()};
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            std::cout << "Shot \n";
            saveMousePosition = {mousePos.x,mousePos.y};
            ChangeState(States::SHOOTING);
        }
    }

    void TrailDraw(Vector2 &playerPos){
        Vector2 mousePos = {(float)GetMouseX(),(float)GetMouseY()};

        for (int i = 0; i < dotQuantit; ++i){
            Vector2 dotPositions = CalculateParabolaPoint(playerPos, mousePos, i);
            DrawCircle(dotPositions.x,dotPositions.y,dotRadius,dotColor);
        }
    }

    Color BulletColor(){
        switch (actualHability)
        {
        case ShotHabilities::STEAM:
            return DARKGRAY;
            break;
        case ShotHabilities::PLASMA:
            return ORANGE;
            break;
        case ShotHabilities::STORM:
            return DARKBLUE;
            break;
        default:
            return GRAY;
            break;
        }
    }

    void ShootingUpdate(){
        currentFrame += 0.1f;
        //std::cout << "Current frame : " << currentFrame << '\n';

        // if (currentFrame >= 100){
        //     currentFrame = 0;
        //     ChangeState(States::HITTING);
        // }
    }

    void ShootingDraw(Vector2 &playerPos){
        bulletPosition = CalculateParabolaPoint(playerPos,saveMousePosition,currentFrame,100);
        std::cout << "Bullet position X : " << bulletPosition.x << '\n'
                  << "Bullet position Y : " << bulletPosition.y << '\n'
                  << "Bullet color : (" << BulletColor().r << ", " << BulletColor().g << ", " << BulletColor().b << ")\n";
        DrawCircle(bulletPosition.x,bulletPosition.y,5.f,BulletColor());
    }

public:
    
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

    //Important Methods
    void Update(Vector2 &playerPos){
        switch (actualState){
            case States::AIMING:
                TrailUpdate();
                break;
            case States::SHOOTING:
                ShootingUpdate();
                break;
            case States::HITTING:
                std::cout << "TODO \n";
                break;
        }
    }

    void Draw(Vector2 &playerPos){
        switch (actualState){
            case States::AIMING:
                TrailDraw(playerPos);
                break;
            case States::SHOOTING:
                ShootingDraw(playerPos);
                break;
            case States::HITTING:
                std::cout << "TODO \n";
                break;
        }
    }
};