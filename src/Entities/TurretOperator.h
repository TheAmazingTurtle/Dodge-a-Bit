#pragma once
#include <raylib.h>

#include "../Utils/Config.h"
#include "Turret.h"

#include <bitset>
#include <string>
#include <random>

class TurretOperator
{
public:
    TurretOperator();

    void update(float deltaTime);
    void draw() const;

    bool doTurretsHit(Rectangle hitbox) const;
    bool isCycleFinished() const;
    void resetCycleFlag();

private:
    enum class DisplayState {
        Reveal, Travel, Hidden
    };

    enum class BitwiseOperator {
        NOT,
        AND, OR, XOR,
        SHR, SHL, // ROL, ROR, RCL, RCR, SAR, SAL,
        END
    };

    static std::mt19937 rng;

    int m_bitSequence;
    std::string m_operand;
    std::string m_operator;
    DisplayState m_displayState;
    float m_delay;
    float m_actionTimer;
    float m_movementSpeed;
    float m_textElevation;
    std::vector<Turret> m_turrets;
    bool m_cycleFinished;
    
    void generateNewEquation();
    std::string toString(BitwiseOperator value) const;
    std::string toString(int value) const;
    BitwiseOperator getRandomBitwiseOperator() const;
    int generate8BitValue() const;
    int generateBitOffsetValue() const;
    void decreaseDelay();
    void setTurrets();
};

