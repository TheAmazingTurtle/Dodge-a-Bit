#pragma once
#include <vector>
#include "config.h"
#include "Screen.hpp"
#include "Player.hpp"
#include "Turret.hpp"

class GameScreen : public Screen
{
public:
    GameScreen();

    void draw() const override;
    void update(float deltaTime) override;
private:
    Player player;
    std::vector<Turret> turrets;

    void drawLifeIcon(int index) const;
    void drawHighscore() const;
};
