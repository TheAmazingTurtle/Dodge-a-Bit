#pragma once
#include "IGameState.h"
#include "GameOverState.h"

#include "../Game.h"
#include "../Entities/Player.h"
#include "../Entities/TurretOperator.h"
#include "../Utils/Config.h"

#include <iostream>

class GameplayState : public IGameState{
public:
    GameplayState();
    void Enter(Game& game);
    void Exit(Game& game);
    void Update(Game& game, float deltaTime) ;
    void Draw(Game& game) const;
    std::string GetName() const;
private:
    static constexpr int screenPadding = Config::UNIT_SIZE;
    static constexpr int hudFontSize = 20;
    static constexpr int hudOffsetY = 40;
    static constexpr int HEART_FRAME_COUNT = 8;
    static constexpr float HEART_FRAME_SPEED = 12.0f;

    Player player;
    TurretOperator turretOperator;
    
    Texture2D backgroundImg;
    Texture2D heartSpriteSheet;

    Rectangle heartFrame;
    Rectangle brokenHeartFrame;

    int score;
    int combo;
    int basePoints;
    int highScore;
    float animationTimer;
    bool breakingHeart;
    float breakTimer;

    void DrawHeadUpDisplay() const;
};
