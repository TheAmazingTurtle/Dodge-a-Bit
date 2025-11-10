#pragma once
#include <raylib.h>

#include "config.h"
#include "Turret.h"

#include <bitset>
#include <string>
#include <random>

class Guardian
{
public:
    Guardian();

    void update(float deltaTime);
    void draw() const;

    bool doTurretsHit(Rectangle hitbox) const;

private:
    enum class DisplayState {
        Reveal, Travel, Hidden
    };

    static std::mt19937 rng;
    static const float m_cooldownDuration;
    static const float m_revealDuration;
    static const int m_operatorFontSize;
    static const int m_operandFontSize;
    static const int m_textGap;

    int m_bitSequence;
    std::string m_operand;
    std::string m_operator;
    DisplayState m_displayState;
    float m_delay;
    float m_actionTimer;
    float m_movementSpeed;
    float m_textElevation;
    std::vector<Turret> m_turrets;
    
    void generateNewEquation();
    std::string toString(BitwiseOperator value) const;
    std::string toBinaryString(int value) const;
    BitwiseOperator getRandomBitwiseOperator() const;
    int generate8BitValue() const;
    int generateBitOffsetValue() const;
    void setTurrets();
};

