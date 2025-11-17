#pragma once

class Settings {
public:
    static Settings& GetInstance();

    // Delete copy operations (no copy allowed)
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    // Delete move operations (optional)
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

    bool GetMusicOn() const;
    bool GetSoundOn() const;
    bool GetInstructionDisplayed() const;

    void ToggleMusic();
    void ToggleSound();
    void ToggleInstructionDisplayed();

private:
    Settings();
    ~Settings() = default;

    bool isMusicOn;
    bool isSoundOn;
    bool isInstructionDisplayed;
};