#pragma once
#include <string>

class Game;

class IGameState {
public:
    virtual ~IGameState() = default;

    virtual void Enter(Game& game) = 0;
    virtual void Exit(Game& game) = 0;
    virtual void Update(Game& game, float deltaTime) = 0;
    virtual void Draw(Game& game) const = 0;
    virtual std::string GetName() const = 0;
};
