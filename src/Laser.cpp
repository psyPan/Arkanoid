//
// Created by 潘雙永(HHA) on 2025/4/12.
//
#include "Laser.hpp"
Laser::Laser(const std::string& imagePath, const glm::vec2& pos, float speed): Entity(imagePath), m_speed(speed) {
    m_Transform.translation = pos;
}

void Laser::Update(){
    m_Transform.translation.y += m_speed;
}
