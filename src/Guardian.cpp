#include "Guardian.h"
#include <iostream>

std::mt19937 Guardian::rng(std::random_device{}());
const float Guardian::m_cooldownDuration = 1.5f;
const float Guardian::m_revealDuration = 0.3f;
const int Guardian::m_operatorFontSize = 30;
const int Guardian::m_operandFontSize = 30;
const int Guardian::m_textGap = 20;

Guardian::Guardian() :
    m_bitSequence(0),
    m_operand(""),
    m_operator(""),
    m_displayState(DisplayState::Hidden),
    m_delay(5.0f),
    m_actionTimer(0.0f),
    m_movementSpeed(0.0f),
    m_textElevation(0.0f) {

        m_turrets.reserve(8);
        float yTurretOffset = UNIT_SIZE * 2.0f;
        float xTurretOffset = (SCREEN_WIDTH - (NUM_TURRETS * UNIT_SIZE)) / 2.0f;
        for (int i = 0; i < NUM_TURRETS; i++){
            Vector2 position = {xTurretOffset + (i* UNIT_SIZE), yTurretOffset};
            m_turrets.emplace_back(position);
        }
    }

void Guardian::generateNewEquation(){
    int tentativeResult = 0;
    int operand = 0;
    BitwiseOperator bitwiseOperator;

    while (tentativeResult <= 0 || tentativeResult >= 0xFF) {
        bitwiseOperator = getRandomBitwiseOperator();
        switch (bitwiseOperator) {
            case BitwiseOperator::NOT:
                tentativeResult = 255 - m_bitSequence;
                operand = 0;
                break;
            case BitwiseOperator::AND:
                operand = generate8BitValue();
                tentativeResult = m_bitSequence & operand;
                break;
            case BitwiseOperator::OR:
                operand = generate8BitValue();
                tentativeResult = m_bitSequence | operand;
                break;
            case BitwiseOperator::XOR:
                operand = generate8BitValue();
                tentativeResult = m_bitSequence ^ operand;
                break;
            case BitwiseOperator::SHR:
                operand = generateBitOffsetValue();
                tentativeResult = m_bitSequence >> operand;
                tentativeResult &= 0xFF;
                break;
            case BitwiseOperator::SHL:
                operand = generateBitOffsetValue();
                tentativeResult = m_bitSequence << operand;
                tentativeResult &= 0xFF;
                break;
        // case BinaryOperator::ROL:
        //     binaryOperator = "ROL";
        //     break;
        // case BinaryOperator::ROR:
        //     binaryOperator = "ROR";
        //     break;
        // case BinaryOperator::SAR:
        //     binaryOperator = "SAR";
        //     break;
        // case BinaryOperator::SAL:
        //     binaryOperator = "SAL";
        //     break;
            default:
                break;
        }

        std::cout << toString(bitwiseOperator) << " "  << operand << " = "<< tentativeResult << std::endl;
    }

    m_bitSequence = tentativeResult;

    m_operator = toString(bitwiseOperator);
    m_operand = toBinaryString(operand);

    m_movementSpeed = ((SCREEN_WIDTH/2 + m_textGap) - UNIT_SIZE*2) / ((m_delay - m_revealDuration) * 60);
}

void Guardian::update(float deltaTime) {
    for (Turret &turret: m_turrets) turret.update(deltaTime);

    m_actionTimer += deltaTime;
    switch (m_displayState) {
        case DisplayState::Reveal:
            if (m_revealDuration <= m_actionTimer) {
                m_actionTimer = 0;
                m_displayState = DisplayState::Travel;
            }
            break;
        case DisplayState::Travel:
            m_textElevation += m_movementSpeed;
            if (m_delay - m_revealDuration <= m_actionTimer) {
                m_actionTimer = 0;
                m_textElevation = 0;
                
                setTurrets();
                for (Turret &turret: m_turrets) turret.shootLaser();

                m_displayState = DisplayState::Hidden;
            }
            break;
        case DisplayState::Hidden:
            if (m_cooldownDuration <= m_actionTimer) {
                m_actionTimer = 0;

                generateNewEquation();

                m_displayState = DisplayState::Reveal;
            }
        default: 
            return;
    }
}

void Guardian::draw() const {
    for (const Turret &turret : m_turrets) turret.draw();

    if (m_displayState == DisplayState::Hidden) return;
    const char* operatorText = TextFormat(m_operator.c_str());
    const char* operandText = TextFormat(m_operand.c_str());

    DrawText(operatorText, (SCREEN_WIDTH - MeasureText(operatorText, m_operatorFontSize))/2, SCREEN_WIDTH/2 - m_operatorFontSize - m_textGap - m_textElevation, m_operatorFontSize, WHITE);
    DrawText(operandText, (SCREEN_WIDTH - MeasureText(operandText, m_operandFontSize))/2, SCREEN_WIDTH/2 + m_textGap - m_textElevation, m_operandFontSize, WHITE);
}

bool Guardian::doTurretsHit(Rectangle hitbox) const {
    for (const Turret &turret : m_turrets) {
        if (turret.getIsShooting() && CheckCollisionRecs(hitbox, turret.getLaserHitbox())){
            return true;
        }
    }
    
    return false;
}

std::string Guardian::toString(BitwiseOperator bitwiseOperator) const {
    switch (bitwiseOperator) {
            case BitwiseOperator::NOT:  return "NOT";
            case BitwiseOperator::AND:  return "AND";
            case BitwiseOperator::OR:   return "OR";
            case BitwiseOperator::XOR:  return "XOR";
            case BitwiseOperator::SHR:  return "SHR";
            case BitwiseOperator::SHL:  return "SHL";
        // case BinaryOperator::ROL:
        //     binaryOperator = "ROL";
        //     break;
        // case BinaryOperator::ROR:
        //     binaryOperator = "ROR";
        //     break;
        // case BinaryOperator::SAR:
        //     binaryOperator = "SAR";
        //     break;
        // case BinaryOperator::SAL:
        //     binaryOperator = "SAL";
        //     break;
            default: return "NOT FOUND";
        }
}

std::string Guardian::toBinaryString(int value) const {
    return std::bitset<8>(value).to_string();
}

BitwiseOperator Guardian::getRandomBitwiseOperator() const {
    static std::uniform_int_distribution<int> dist(0, static_cast<int>(BitwiseOperator::END) - 1);
    return static_cast<BitwiseOperator>(dist(rng));
}

int Guardian::generate8BitValue() const {
    static std::uniform_int_distribution<int> dist(0, 255);
    return dist(rng);
}

int Guardian::generateBitOffsetValue() const {
    static std::uniform_int_distribution<int> dist(1, 8);
    return dist(rng);
}

void Guardian::setTurrets() {
    std::string bitString = toBinaryString(m_bitSequence);
    for (int i = 0; i < NUM_TURRETS; i++) {
        bool isTurretActive = bitString[i] == '1';
        m_turrets[i].setIsActive(isTurretActive);
    }
}