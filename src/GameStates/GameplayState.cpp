#include "GameplayState.h"
#include <emscripten.h>

int LoadHighScore() {
    return EM_ASM_INT({
        var score = localStorage.getItem('dodgeabit_highscore');
        return score ? parseInt(score) : 0;
    });
}


GameplayState::GameplayState() : player(), turretOperator(), score(0), combo(0), basePoints(100), highScore(0), hasNewHighScore(false), animationTimer(0.0f), breakingHeart(false), breakTimer(0.0f) {
    backgroundImg = LoadTexture("../../graphics/game-background.png");
    heartSpriteSheet = LoadTexture("../../graphics/heart-spritesheet.png");
    heartFrame = {0.0f, 0.0f, Config::UNIT_SIZE, Config::UNIT_SIZE};
    brokenHeartFrame = {0.0f, Config::UNIT_SIZE, Config::UNIT_SIZE, Config::UNIT_SIZE};
}
    
void GameplayState::Enter(Game& game) {
    highScore = LoadHighScore();
}

void GameplayState::Exit(Game& game){

}

void GameplayState::Update(Game& game, float deltaTime){
    animationTimer += deltaTime;
    if (animationTimer >= 1.0f / HEART_FRAME_SPEED) {
        animationTimer = 0.0f;
        if (heartFrame.x + Config::UNIT_SIZE < HEART_FRAME_COUNT * Config::UNIT_SIZE)
            heartFrame.x += Config::UNIT_SIZE;    
        else
            heartFrame.x = 0.0f;
    }

    if (breakingHeart) {
        breakTimer += deltaTime;
        if (breakTimer >= 1.0f / HEART_FRAME_SPEED) {
            animationTimer = 0.0f;
            if (brokenHeartFrame.x + Config::UNIT_SIZE < HEART_FRAME_COUNT * Config::UNIT_SIZE)
                brokenHeartFrame.x += Config::UNIT_SIZE;    
            else {
                brokenHeartFrame.x = 0.0f;
                breakingHeart = false;
            }
        }
    }

    player.Update(deltaTime);
    turretOperator.update(deltaTime);
    
    if (!player.IsHit() && turretOperator.doTurretsHit(player.GetHitbox())) {
        player.TakeHit();
        breakingHeart = true;
    }

    if (turretOperator.isCycleFinished()) {
        if (!player.IsHit()) {
            const int points = basePoints * (1 + combo * 0.2f);  

            score += points;
            if (score > highScore) {
                highScore = score;
                hasNewHighScore = true;
            }
            combo++;
        } else {
            combo = 0;
        }

        std::cout << turretOperator.isCycleFinished() << ' ' << player.IsHit() << ' ' << score << std::endl;

        player.ResetHitFlags();
        turretOperator.resetCycleFlag();
    }

    if (player.GetLivesLeft() <= 0) {
        if (score > highScore){
            highScore = score;
        }
        game.ChangeState(std::make_unique<GameOverState>(score, highScore, hasNewHighScore));
    }
}

void GameplayState::Draw(Game& game) const{
    DrawTexture(backgroundImg, 0, 0, WHITE);

    DrawHeadUpDisplay();

    turretOperator.draw();
    player.Draw();
}

std::string GameplayState::GetName() const {
    return "Gameplay State";
}

void GameplayState::DrawHeadUpDisplay() const {
    const char* scoreText = TextFormat("Score: %d", score);
    const char* highScoreText = TextFormat("High Score: %d", highScore);

    DrawText(scoreText, (Config::SCREEN_WIDTH - MeasureText(scoreText, hudFontSize))/2.2, hudOffsetY, hudFontSize, WHITE);
    DrawText(highScoreText, Config::SCREEN_WIDTH - MeasureText(highScoreText, hudFontSize) - screenPadding, hudOffsetY, hudFontSize, WHITE);

    // Draw lives
    float offsetX = screenPadding - 17;
    float offsetY = hudOffsetY - 18;
    int heartGap = 47;
    for (int i = 0; i < player.GetLivesLeft(); i++) {
        DrawTextureRec(heartSpriteSheet, heartFrame, {offsetX, offsetY}, WHITE);
        offsetX += heartGap;
    }

    if (breakingHeart) {
        DrawTextureRec(heartSpriteSheet, brokenHeartFrame, {offsetX, offsetY}, WHITE);
    }


}
