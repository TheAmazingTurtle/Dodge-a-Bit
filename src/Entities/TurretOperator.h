#pragma once
#include <raylib.h>

#include "../Utils/Config.h"
#include "Turret.h"

#include <cstdint>
#include <cmath>
#include <bitset>
#include <string>
#include <random>

class TurretOperator
{
public:
    TurretOperator();
    ~TurretOperator();

    void update(float deltaTime);
    void draw() const;

    bool doTurretsHit(Rectangle hitbox) const;
    bool isCycleFinished() const;
    void resetCycleFlag();

private:
    enum class DisplayState {
        Travel, Hidden,
        Appear, Pop
    };

    enum class BitwiseOperator {
        NOT, AND, OR, XOR,
        SHR, SHL, ROL, ROR, 
        SAR, RCL, RCR,
        END
    };

    static constexpr float COOLDOWN_DURATION = 2.0f;
    static constexpr float DELAY_DECAY_RATE = 0.1f;
    static constexpr float MINIMUM_DELAY = 2.0f;
    static constexpr float REVEAL_DURATION = 0.3f;
    static constexpr int OPERATOR_FONT_SIZE = 30;
    static constexpr int OPERAND_FONT_SIZE = 30;
    static constexpr int OPERAND_BUBBLE_SIZE = Config::UNIT_SIZE * 1.8f;
    static constexpr int BUBBLE_FRAME_COUNT = 20;
    static constexpr int BUBBLE_FRAME_SPEED = 12;
    static constexpr int TEXT_GAP = 20;

    static std::mt19937 rng;

    // Sound m_laserSFX;
    Texture2D m_bubbleSpriteSheet;
    Rectangle m_bubbleSpriteFrame;

    int m_progLvl;
    int m_numCycle;
    uint8_t m_bitSequence;
    std::string m_operand;
    std::string m_operator;
    DisplayState m_displayState;
    float m_delay;
    float m_actionTimer;
    float m_movementSpeed;
    float m_textElevation;
    std::vector<Turret> m_turrets;
    bool m_cycleFinished;
    bool m_setCarryFlag;
    
    void generateNewEquation();
    std::string toString(BitwiseOperator value) const;
    std::string toBitString(int value) const;
    std::string toNumString(int value) const;
    BitwiseOperator getRandomBitwiseOperator() const;
    uint8_t generate8BitValue() const;
    int generateBitOffsetValue() const;
    void decreaseDelay();
    void setTurrets();
};

