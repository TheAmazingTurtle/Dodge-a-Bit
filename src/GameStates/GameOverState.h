#pragma once

#include "../Game.h"
#include "../Utils/Config.h"
#include "../Utils/Button.h"

#include "IGameState.h"
#include "StartState.h"
#include "GameplayState.h"

class GameOverState : public IGameState {
public:
    GameOverState();

    void Enter(Game& game);
    void Exit(Game& game);
    void Update(Game& game, float deltaTime);
    void Draw(Game& game) const;
    std::string GetName() const;

private:
    enum class ButtonAction {
        None,
        MainMenu, TryAgain, Exit
    };

    Button mainMenuButton;
    Button tryAgainButton;
    Button exitButton;

    ButtonAction GetButtonAction(Vector2 mousePosition) const;
};