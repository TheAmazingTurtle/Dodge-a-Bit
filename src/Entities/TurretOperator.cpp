#include "TurretOperator.h"

std::mt19937 TurretOperator::rng(std::random_device{}());

TurretOperator::TurretOperator() :
    m_progLvl(1),
    m_numCycle(0),
    m_bitSequence(0),
    m_operand(""),
    m_operator(""),
    m_displayState(DisplayState::Appear),
    m_delay(3.0f),
    m_actionTimer(0.0f),
    m_movementSpeed(0.0f),
    m_textElevation(0.0f),
    m_cycleFinished(false),
    m_setCarryFlag(false) {

        // Sound m_laserSFX = LoadSound("../../sfx/laser-sfx.wav");
        // PlaySound(m_laserSFX);

        m_bubbleSpriteSheet = LoadTexture("../../graphics/bubble-spritesheet.png");
        m_bubbleSpriteFrame = {0.0f, 0.0f, Config::UNIT_SIZE, Config::UNIT_SIZE};

        m_turrets.reserve(8);
        float yTurretOffset = Config::UNIT_SIZE * 2.0f;
        float xTurretOffset = (Config::SCREEN_WIDTH - (Config::TURRET_NUM * Config::UNIT_SIZE)) / 2.0f;
        for (int i = 0; i < Config::TURRET_NUM; i++){
            Vector2 position = {xTurretOffset + (i * Config::UNIT_SIZE), yTurretOffset};
            m_turrets.emplace_back(position);
        }

        generateNewEquation();
    }

TurretOperator::~TurretOperator() {
    UnloadTexture(m_bubbleSpriteSheet);
    // UnloadSound(m_laserSFX);
    
} 

void TurretOperator::generateNewEquation(){
    uint8_t tentativeResult = 0;
    uint8_t operand = 0;
    bool setCarryFlag = false;
    BitwiseOperator bitwiseOperator;

    while (tentativeResult == 0 || tentativeResult == 0xFF) {
        bitwiseOperator = getRandomBitwiseOperator();

        int8_t temp;
        switch (bitwiseOperator) {
            case BitwiseOperator::NOT:
                tentativeResult = ~m_bitSequence;
                operand = 0;
                setCarryFlag = m_setCarryFlag;
                break;

            case BitwiseOperator::AND:
                operand = generate8BitValue();
                tentativeResult = m_bitSequence & operand;
                setCarryFlag = false;
                break;

            case BitwiseOperator::OR:
                operand = generate8BitValue();
                tentativeResult = m_bitSequence | operand;
                setCarryFlag = false;
                break;

            case BitwiseOperator::XOR:
                operand = generate8BitValue();
                tentativeResult = m_bitSequence ^ operand;
                setCarryFlag = false;
                break;

            case BitwiseOperator::SHR:
                operand = generateBitOffsetValue();
                tentativeResult = m_bitSequence >> operand;
                setCarryFlag = m_bitSequence >> (operand - 1) & 1;
                tentativeResult &= 0xFF;
                break;

            case BitwiseOperator::SHL:
                operand = generateBitOffsetValue();
                tentativeResult = m_bitSequence << operand;
                setCarryFlag = (m_bitSequence << (operand - 1) & 0x80) != 0;
                break;

            case BitwiseOperator::ROL:
                operand = generateBitOffsetValue();
                tentativeResult = (m_bitSequence << operand) | (m_bitSequence >> (Config::TURRET_NUM - operand));
                setCarryFlag = tentativeResult & 1;
                break;

            case BitwiseOperator::ROR:
                operand = generateBitOffsetValue();
                tentativeResult = (m_bitSequence >> operand) | (m_bitSequence << (Config::TURRET_NUM - operand));
                setCarryFlag = (tentativeResult & 0x80) != 0;
                break;

            case BitwiseOperator::SAR:
                operand = generateBitOffsetValue();
                temp = static_cast<int8_t>(m_bitSequence);
                tentativeResult = static_cast<uint8_t>(temp >> operand);
                setCarryFlag = m_bitSequence >> (operand - 1) & 1;
                break;

            case BitwiseOperator::RCL:
                operand = generateBitOffsetValue();
                tentativeResult = (m_bitSequence << operand) | (m_bitSequence >> (Config::TURRET_NUM - operand));
                if (setCarryFlag) 
                    tentativeResult |= 1 << (operand - 1);
                else 
                    tentativeResult &= ~(1 << (operand - 1));
                setCarryFlag = (m_bitSequence >> (Config::TURRET_NUM - operand)) & 1;
                break;
            
            case BitwiseOperator::RCR:
                operand = generateBitOffsetValue();

                tentativeResult = (m_bitSequence >> operand) | (m_bitSequence << (Config::TURRET_NUM - operand));
                if (setCarryFlag)
                    tentativeResult |= 1 << (Config::TURRET_NUM - (operand));
                else
                    tentativeResult &= ~(1 << (Config::TURRET_NUM - operand));
                setCarryFlag = (m_bitSequence >> (operand - 1)) & 1;
                break;

            default:
                break;
        }
    }

    m_bitSequence = tentativeResult;

    m_operator = toString(bitwiseOperator);

    switch (bitwiseOperator) {
            case BitwiseOperator::NOT:
                m_operand = "";
                break;
            case BitwiseOperator::AND:
            case BitwiseOperator::OR:
            case BitwiseOperator::XOR:
                m_operand = toBitString(operand);
                break;
            default:
                m_operand = toNumString(operand);
                break;
        }
    

    m_movementSpeed = ((Config::SCREEN_HEIGHT - OPERAND_BUBBLE_SIZE)/2 - Config::UNIT_SIZE*3.8f) / ((m_delay - REVEAL_DURATION) * 60);
}

void TurretOperator::update(float deltaTime) {
    for (Turret &turret: m_turrets) turret.update(deltaTime);

    switch (m_numCycle) {
        case 0: m_progLvl = 1; break;
        case 10: m_progLvl = 2; break;
        case 15: m_progLvl = 3; break;
        case 20: m_progLvl = 4; break;
        case 25: m_progLvl = 5; break;
        default: break;
    }

    m_actionTimer += deltaTime;
    switch (m_displayState) {

        case DisplayState::Appear:
            if ((int)m_bubbleSpriteFrame.x < Config::UNIT_SIZE * 13){
                if (m_actionTimer >= 1.0f/BUBBLE_FRAME_SPEED){
                    m_actionTimer = 0;
                    m_bubbleSpriteFrame.x += Config::UNIT_SIZE;
                }
                return;
            }
            m_displayState = DisplayState::Travel;
        case DisplayState::Travel:
            m_textElevation += m_movementSpeed;
            if (m_delay - REVEAL_DURATION <= m_actionTimer) {
                m_actionTimer = 0;
                m_displayState = DisplayState::Pop;
            }
            break;

        case DisplayState::Pop:
            if ((int)m_bubbleSpriteFrame.x < Config::UNIT_SIZE * BUBBLE_FRAME_COUNT){
                if (m_actionTimer >= 1.0f/BUBBLE_FRAME_SPEED){
                    m_actionTimer = 0;
                    m_bubbleSpriteFrame.x += Config::UNIT_SIZE;
                }
                return;
            }
            setTurrets();
            for (Turret &turret: m_turrets) turret.shootLaser();
            // PlaySound(m_laserSFX);

            
            m_textElevation = 0;
            m_bubbleSpriteFrame.x = 0.0f;
            m_displayState = DisplayState::Hidden;

        case DisplayState::Hidden:
            if (COOLDOWN_DURATION <= m_actionTimer) {
                m_actionTimer = 0;

                generateNewEquation();
                decreaseDelay();

                m_cycleFinished = true;
                m_displayState = DisplayState::Appear;
                if (m_numCycle <= 25) m_numCycle++;
            }
            break;

        default: 
            return;
    }
}

void TurretOperator::draw() const {
    for (const Turret &turret : m_turrets) turret.draw();

    if (m_displayState == DisplayState::Hidden) return;

    
    const float xOperandPos = (Config::SCREEN_WIDTH - OPERAND_BUBBLE_SIZE)/2;
    const float yOperandPos = Config::SCREEN_HEIGHT/2 - OPERAND_BUBBLE_SIZE - m_textElevation;
    DrawTexturePro(m_bubbleSpriteSheet, m_bubbleSpriteFrame, {xOperandPos, yOperandPos, OPERAND_BUBBLE_SIZE, OPERAND_BUBBLE_SIZE}, {0.0f, 0.0f}, 0.0f, WHITE);
    
    for (size_t i = 0; i < m_operand.length(); i++) {
        const float xPos = (Config::SCREEN_WIDTH-Config::UNIT_SIZE*m_operand.length())/2.0f + i*Config::UNIT_SIZE;
        const float yPos = Config::SCREEN_HEIGHT/2.0f - m_textElevation;

        DrawTextureRec(m_bubbleSpriteSheet, m_bubbleSpriteFrame, {xPos, yPos}, WHITE);
    }

    if (m_displayState != DisplayState::Travel) return;

    const char* operatorText = TextFormat(m_operator.c_str());
    DrawText(operatorText, xOperandPos + (OPERAND_BUBBLE_SIZE - MeasureText(operatorText, OPERATOR_FONT_SIZE))/2, yOperandPos + (OPERAND_BUBBLE_SIZE - OPERAND_FONT_SIZE)/2, OPERATOR_FONT_SIZE, WHITE);
    
    const char* p = m_operand.c_str();
    for (int i = 0; *p != '\0'; i++, p++) {
        const char* bitText = TextFormat("%c", *p);
        const float xPos = (Config::SCREEN_WIDTH-Config::UNIT_SIZE*m_operand.length())/2 + (Config::UNIT_SIZE - MeasureText(bitText, OPERAND_FONT_SIZE))/2  + i*Config::UNIT_SIZE;
        const float yPos = Config::SCREEN_HEIGHT/2 + (Config::UNIT_SIZE - OPERAND_FONT_SIZE)/2  - m_textElevation;

        DrawText(bitText, xPos, yPos, OPERAND_FONT_SIZE, WHITE);
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
            case BitwiseOperator::ROL:  return "ROL";
            case BitwiseOperator::ROR:  return "ROR";
            case BitwiseOperator::SAR:  return "SAR";
            case BitwiseOperator::RCL:  return "RCL";
            case BitwiseOperator::RCR:  return "RCR";
            default: return "NOT FOUND";
        }
}

std::string TurretOperator::toBitString(int value) const {
    return std::bitset<8>(value).to_string();
}

std::string TurretOperator::toNumString(int value) const {
    return std::to_string(value);
}

TurretOperator::BitwiseOperator TurretOperator::getRandomBitwiseOperator() const {
    std::uniform_int_distribution<int> dist;
    switch (m_progLvl) {
        case 1:
            dist = std::uniform_int_distribution<int>(static_cast<int>(BitwiseOperator::NOT), static_cast<int>(BitwiseOperator::XOR));
            break;
        case 2:
            dist = std::uniform_int_distribution<int>(static_cast<int>(BitwiseOperator::SHR), static_cast<int>(BitwiseOperator::SHL));
            break;
        case 3:
            dist = std::uniform_int_distribution<int>(static_cast<int>(BitwiseOperator::ROL), static_cast<int>(BitwiseOperator::ROR));
            break;
        case 4:
            dist = std::uniform_int_distribution<int>(static_cast<int>(BitwiseOperator::SAR), static_cast<int>(BitwiseOperator::RCR));
            break;
        default:
            dist = std::uniform_int_distribution<int>(static_cast<int>(BitwiseOperator::NOT), static_cast<int>(BitwiseOperator::END) - 1);
            break;
    }

    
    return static_cast<BitwiseOperator>(dist(rng));
}

uint8_t TurretOperator::generate8BitValue() const {
    static std::uniform_int_distribution<int> dist(0, 255);
    return static_cast<uint8_t>(dist(rng));
}

int TurretOperator::generateBitOffsetValue() const {
    static std::uniform_int_distribution<int> dist(1, 8);
    return dist(rng);
}

void TurretOperator::decreaseDelay() {
    if (m_delay <= MINIMUM_DELAY) return;
    m_delay -= DELAY_DECAY_RATE;
};

void TurretOperator::setTurrets() {
    std::string bitString = toBitString(m_bitSequence);
    for (int i = 0; i < Config::TURRET_NUM; i++) {
        bool isTurretActive = bitString[i] == '1';
        m_turrets[i].setIsActive(isTurretActive);
    }
}