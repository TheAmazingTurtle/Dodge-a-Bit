#pragma once
#include "IGameState.h"
#include "GameOverState.h"

#include "../Game.h"
#include "../Entities/Player.h"
#include "../Entities/TurretOperator.h"
#include "../Utils/UIRenderer.h"

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
    Player player;
    TurretOperator turretOperator;
    
    int score;
    int combo;
    int basePoints;
    int highScore;

};
