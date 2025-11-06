#include "StartScreen.h"

StartScreen::StartScreen() 
    :   playButton("Play", { 0,0 }, { 200, 60 }),
        musicButton("Music: ON", { 0,0 }, { 200, 60 }),
        soundButton("Sounds: ON", { 0,0 }, { 200, 60 }),
        instructionsButton("Instructions", { 0,0 }, { 200, 60 }),
        exitButton("Exit", { 0,0 }, { 200, 60 }),
        isMusicOn(true),
        isSoundOn(true),
        isInstructionDisplayed(false)
{
    float centerX = (GetScreenWidth() - 200) / 2;
    float startY = 300;
    float spacing = 80;

    Button* buttons[] = { &playButton, &musicButton, &soundButton, &instructionsButton, &exitButton };

    for (int i = 0; i < 5; i++) {
        buttons[i]-> SetPosition ({ centerX, startY + spacing * i });
    }

}
StartScreen::~StartScreen() {}

void StartScreen::Draw() const{
    DrawGameTitle();
    DrawButtons();
}

void StartScreen::Update() {
    startAction = StartScreenAction::None;
    Vector2 mousePos = GetMousePosition();
    bool isClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (playButton.IsPressed(mousePos, isClicked)) startAction = StartScreenAction::Play;
    else if (musicButton.IsPressed(mousePos, isClicked)){
        startAction = StartScreenAction::ToggleMusic;
        isMusicOn = !isMusicOn;
        musicButton.SetLabel(isMusicOn ? "Music : ON" : "Music : OFF");

    } else if (soundButton.IsPressed(mousePos, isClicked)) {
        startAction = StartScreenAction::ToggleSound;
        isSoundOn = !isSoundOn;
        soundButton.SetLabel(isSoundOn ? "Sound : ON" : "Sound: OFF");

    } else if (instructionsButton.IsPressed(mousePos, isClicked)){
        startAction = StartScreenAction::DisplayInstructions;
        isInstructionDisplayed = !isInstructionDisplayed;

    } else if (exitButton.IsPressed(mousePos, isClicked)) startAction = StartScreenAction::Exit;
}

bool StartScreen::IsPlayPressed() const{return startAction == StartScreenAction::Play;}
// bool StartScreen::IsMusicPressed() const{return startAction == StartScreenAction::ToggleMusic;}
// bool StartScreen::IsSoundPressed() const{return startAction == StartScreenAction::ToggleSound;}
// bool StartScreen::IsInstructionPressed() const{return startAction == StartScreenAction::DisplayInstructions;}
bool StartScreen::IsExitPressed() const{return startAction == StartScreenAction::Exit;}

void StartScreen::DrawGameTitle() const{
    const char* gameTitle = "Dodge-a-Bit";
    int fontSize = 50;
    int textWidth = MeasureText(gameTitle, fontSize);

    DrawText(gameTitle, (GetScreenWidth() - textWidth) / 2, 150, fontSize, WHITE);
}

void StartScreen::DrawButtons() const{
    playButton.Draw();
    musicButton.Draw();
    soundButton.Draw();
    instructionsButton.Draw();
    exitButton.Draw();
}