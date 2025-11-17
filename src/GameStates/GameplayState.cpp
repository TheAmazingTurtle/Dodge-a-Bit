#include "GameplayState.h"
    

GameplayState::GameplayState() : player(), turretOperator(), score(0), combo(0), basePoints(100), highScore(0) {}
    
void GameplayState::Enter(Game& game) {

}

void GameplayState::Exit(Game& game){

}

void GameplayState::Update(Game& game, float deltaTime){
    player.Update(deltaTime);
    turretOperator.update(deltaTime);
    
    if (!player.IsHit() && turretOperator.doTurretsHit(player.GetHitbox())) {
        player.TakeHit();
    }

    if (turretOperator.isCycleFinished()) {
        if (!player.IsHit()) {
            const int points = basePoints * (1 + combo * 0.2f);  

            score += points;
            combo++;
        } else {
            combo = 0;
        }

        std::cout << turretOperator.isCycleFinished() << ' ' << player.IsHit() << ' ' << score << std::endl;

        player.ResetHitFlags();
        turretOperator.resetCycleFlag();
    }
}

void GameplayState::Draw(Game& game) const{
    ClearBackground(BLACK);

    UIRenderer::drawHeadupDisplay(player.GetLivesLeft(), score, highScore);
    turretOperator.draw();
    player.Draw();
}

std::string GameplayState::GetName() const {
    return "Gameplay State";
}
