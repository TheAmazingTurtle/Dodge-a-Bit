#include "TurretOperator.h"
#include <iostream>

std::mt19937 TurretOperator::rng(std::random_device{}());

TurretOperator::TurretOperator() :
    m_bitSequence(0),
    m_operand(""),
    m_operator(""),
    m_displayState(DisplayState::Reveal),
    m_delay(5.0f),
    m_actionTimer(0.0f),
    m_movementSpeed(0.0f),
    m_textElevation(0.0f),
    m_cycleFinished(false) {

        m_turrets.reserve(8);
        float yTurretOffset = Config::UNIT_SIZE * 2.0f;
        float xTurretOffset = (Config::SCREEN_WIDTH - (Config::TURRET_NUM * Config::UNIT_SIZE)) / 2.0f;
        for (int i = 0; i < Config::TURRET_NUM; i++){
            Vector2 position = {xTurretOffset + (i * Config::UNIT_SIZE), yTurretOffset};
            m_turrets.emplace_back(position);
        }

        generateNewEquation();
    }

void TurretOperator::generateNewEquation(){
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
    m_operand = toString(operand);

    m_movementSpeed = ((Config::SCREEN_WIDTH/2 + Config::EQUATION_TEXT_GAP) - Config::UNIT_SIZE*2) / ((m_delay - Config::EQUATION_REVEAL_DURATION) * 60);
}

void TurretOperator::update(float deltaTime) {
    for (Turret &turret: m_turrets) turret.update(deltaTime);

    m_actionTimer += deltaTime;
    switch (m_displayState) {
        case DisplayState::Reveal:
            if (Config::EQUATION_REVEAL_DURATION <= m_actionTimer) {
                m_actionTimer = 0;
                m_displayState = DisplayState::Travel;
            }
            break;
        case DisplayState::Travel:
            m_textElevation += m_movementSpeed;
            if (m_delay - Config::EQUATION_REVEAL_DURATION <= m_actionTimer) {
                m_actionTimer = 0;
                m_textElevation = 0;
                
                setTurrets();
                for (Turret &turret: m_turrets) turret.shootLaser();

                m_displayState = DisplayState::Hidden;
            }
            break;
        case DisplayState::Hidden:
            if (Config::EQUATION_COOLDOWN_DURATION <= m_actionTimer) {
                m_actionTimer = 0;

                generateNewEquation();
                decreaseDelay();

                m_cycleFinished = true;
                m_displayState = DisplayState::Reveal;
            }
        default: 
            return;
    }
}

void TurretOperator::draw() const {
    for (const Turret &turret : m_turrets) turret.draw();

    if (m_displayState == DisplayState::Hidden) return;
    const char* operatorText = TextFormat(m_operator.c_str());
    // const char* operandText = TextFormat(m_operand.c_str());

    DrawText(operatorText, (Config::SCREEN_WIDTH - MeasureText(operatorText, Config::EQUATION_OPERATOR_FONT_SIZE))/2, Config::SCREEN_WIDTH/2 - Config::EQUATION_OPERATOR_FONT_SIZE - Config::EQUATION_TEXT_GAP - m_textElevation, Config::EQUATION_OPERATOR_FONT_SIZE, WHITE);
    // DrawText(operandText, (Config::SCREEN_WIDTH - MeasureText(operandText, Config::EQUATION_OPERAND_FONT_SIZE))/2, Config::SCREEN_WIDTH/2 + Config::EQUATION_TEXT_GAP - m_textElevation, Config::EQUATION_OPERAND_FONT_SIZE, WHITE);


    const char* p = m_operand.c_str();
    for (int i = 0; *p != '\0'; i++, p++) {
        const char* bitText = TextFormat("%c", *p);
        DrawText(bitText, (Config::SCREEN_WIDTH - Config::UNIT_SIZE*Config::TURRET_NUM)/2 + Config::UNIT_SIZE*i + (Config::UNIT_SIZE - MeasureText(bitText, Config::EQUATION_OPERAND_FONT_SIZE))/2, Config::SCREEN_WIDTH/2 + Config::EQUATION_TEXT_GAP - m_textElevation, Config::EQUATION_OPERAND_FONT_SIZE, WHITE);
    }


}

bool TurretOperator::doTurretsHit(Rectangle hitbox) const {
    for (const Turret &turret : m_turrets) {
        if (turret.getIsShooting() && CheckCollisionRecs(hitbox, turret.getLaserHitbox())){
            return true;
        }
    }
    
    return false;
}

bool TurretOperator::isCycleFinished() const {
    return m_cycleFinished;
}

void TurretOperator::resetCycleFlag() {
    m_cycleFinished = false;
}

std::string TurretOperator::toString(BitwiseOperator bitwiseOperator) const {
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

std::string TurretOperator::toString(int value) const {
    return std::bitset<8>(value).to_string();
}

TurretOperator::BitwiseOperator TurretOperator::getRandomBitwiseOperator() const {
    static std::uniform_int_distribution<int> dist(0, static_cast<int>(BitwiseOperator::END) - 1);
    return static_cast<BitwiseOperator>(dist(rng));
}

int TurretOperator::generate8BitValue() const {
    static std::uniform_int_distribution<int> dist(0, 255);
    return dist(rng);
}

int TurretOperator::generateBitOffsetValue() const {
    static std::uniform_int_distribution<int> dist(1, 8);
    return dist(rng);
}

void TurretOperator::decreaseDelay() {
    if (m_delay <= Config::EQUATION_MINIMUM_DELAY) return;
    m_delay -= Config::EQUATION_DELAY_DECAY_RATE;
};

void TurretOperator::setTurrets() {
    std::string bitString = toString(m_bitSequence);
    for (int i = 0; i < Config::TURRET_NUM; i++) {
        bool isTurretActive = bitString[i] == '1';
        m_turrets[i].setIsActive(isTurretActive);
    }
}