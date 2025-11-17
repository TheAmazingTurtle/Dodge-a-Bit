#include "Settings.h"

Settings::Settings() : isMusicOn(true), isSoundOn(true), isInstructionDisplayed(true) {}

Settings& Settings::GetInstance() {
    static Settings instance;  
    return instance;
}

bool Settings::GetMusicOn() const { return isMusicOn; }
bool Settings::GetSoundOn() const { return isSoundOn; }
bool Settings::GetInstructionDisplayed() const { return isInstructionDisplayed; }

void Settings::ToggleMusic() { isMusicOn = !isMusicOn; }
void Settings::ToggleSound() { isSoundOn = !isSoundOn; }
void Settings::ToggleInstructionDisplayed() { isInstructionDisplayed = !isInstructionDisplayed; }