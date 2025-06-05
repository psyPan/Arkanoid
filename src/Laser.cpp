//
// Created by 潘雙永(HHA) on 2025/4/12.
//
#include "Laser.hpp"
#include <iostream>
Laser::Laser(const std::string& imagePath, const glm::vec2& pos, float speed, int trajectory): Entity(imagePath), m_speed(speed), active(true), m_trajectory(trajectory) {
    m_Transform.translation = pos;
}

void Laser::Update(const glm::vec2& screenSize){
    float deltaY = (m_trajectory > 0 ? 1.0f : -1.0f) * m_speed;
    m_Transform.translation += (m_direction_unit_vector * deltaY);
    // Deactivate if out of screen bounds
    if (IsActive()) {
        float halfHeight = GetScaledSize().y / 2;
        float yPos = m_Transform.translation.y;

        if ((m_trajectory > 0 && yPos + halfHeight > screenSize.y / 2 - 24) ||
            (m_trajectory < 0 && yPos - halfHeight < -screenSize.y / 2 + 24)) {
            active = false;
            }
    }
}

// void Laser::MoveTowardsVaus(const glm::vec2& DOHPos, const glm::vec2& vausPos, const glm::vec2& screenSize){
//
//     if (IsActive()) {
//         float halfHeight = GetScaledSize().y / 2;
//         float yPos = m_Transform.translation.y;
//
//         if ((m_trajectory > 0 && yPos + halfHeight > screenSize.y / 2 - 24) ||
//             (m_trajectory < 0 && yPos - halfHeight < -screenSize.y / 2 + 24)) {
//             active = false;
//             }
//     }
// }
