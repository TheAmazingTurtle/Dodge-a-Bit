#pragma once

#include "../Game.h"

#include "../Utils/Config.h"
#include "../Utils/Settings.h"
#include "../Utils/Button.h"

#include "IGameState.h"
#include "GameplayState.h"

class StartState : public IGameState{
public:
    StartState();

    void Enter(Game& game);
    void Exit(Game& game);
    void Update(Game& game, float deltaTime);
    void Draw(Game& game) const;
    std::string GetName() const;

private:
    enum class ButtonAction {
        None, Play, Exit,
        ToggleMusic, ToggleSound,
        DisplayInstructions
    };

    Button playButton;
    Button musicButton; 
    Button soundButton;
    Button instructionsButton;
    Button exitButton;

    ButtonAction GetButtonAction(Vector2 mousePosition) const;
};