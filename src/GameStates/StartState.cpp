#include "StartState.h"



StartState::StartState() :
    playButton("Play", { 0,0 }, { 200, 60 }),
    musicButton("Music: ON", { 0,0 }, { 200, 60 }),
    soundButton("Sounds: ON", { 0,0 }, { 200, 60 }),
    instructionsButton("Instructions", { 0,0 }, { 200, 60 }),
    exitButton("Exit", { 0,0 }, { 200, 60 }) {
        
        float centerX = (Config::SCREEN_WIDTH - 200) / 2;

        std::cout << centerX << std::endl;

        float startY = 300;
        float spacing = 80;

        Button* buttons[] = { &playButton, &musicButton, &soundButton, &instructionsButton, &exitButton };

        for (int i = 0; i < 5; i++) {
            buttons[i]-> SetPosition ({ centerX, startY + spacing * i });
        }
    }

void StartState::Enter(Game& game) {

}

void StartState::Exit(Game& game) {

}

void StartState::Update(Game& game, float deltaTime) {
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;

    switch (GetButtonAction(GetMousePosition())) {
        case ButtonAction::Play:
            game.ChangeState(std::make_unique<GameplayState>());
            break;
        case ButtonAction::ToggleMusic:
            Settings::GetInstance().ToggleMusic();
            musicButton.SetLabel(Settings::GetInstance().GetMusicOn() ? "Music : ON" : "Music : OFF");
            break;
        case ButtonAction::ToggleSound:
            Settings::GetInstance().ToggleSound();
            soundButton.SetLabel(Settings::GetInstance().GetSoundOn() ? "Sound : ON" : "Sound : OFF");
            break;
        case ButtonAction::DisplayInstructions:
            Settings::GetInstance().ToggleInstructionDisplayed();
            break;
        case ButtonAction::Exit:
            game.EndGame();
            return;
        default:
            break;
    }
}

void StartState::Draw(Game& game) const {
    const char* gameTitle = "Dodge-a-Bit";
    int fontSize = 50;
    int textWidth = MeasureText(gameTitle, fontSize);
    DrawText(gameTitle, (GetScreenWidth() - textWidth) / 2, 150, fontSize, WHITE);

    playButton.Draw();
    musicButton.Draw();
    soundButton.Draw();
    instructionsButton.Draw();
    exitButton.Draw();
}

std::string StartState::GetName() const {
    return "Start State";
}

StartState::ButtonAction StartState::GetButtonAction(Vector2 mousePosition) const {
    if (playButton.IsPressed(mousePosition, true)) return ButtonAction::Play;
    if (musicButton.IsPressed(mousePosition, true)) return ButtonAction::ToggleMusic;
    if (soundButton.IsPressed(mousePosition, true)) return ButtonAction::ToggleSound;
    if (instructionsButton.IsPressed(mousePosition, true)) return ButtonAction::DisplayInstructions;
    if (exitButton.IsPressed(mousePosition, true)) return ButtonAction::Exit;
    return ButtonAction::None;
}