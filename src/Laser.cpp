//
// Created by 潘雙永(HHA) on 2025/4/12.
//
#include "Laser.hpp"
Laser::Laser(const std::string& imagePath, const glm::vec2& pos, float speed): Entity(imagePath), m_speed(speed), active(true) {
    m_Transform.translation = pos;
}

void Laser::Update(const glm::vec2& screenSize){
    m_Transform.translation.y += m_speed;
    if (IsActive()){
        if (m_Transform.translation. y + GetScaledSize().y/2 > screenSize.y/2 - 24){
            active = false;
        }
    }
}
