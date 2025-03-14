//
// Created by 潘雙永(HHA) on 2025/3/13.
//

#include "Ball.hpp"
#include <cmath>
// float Ball::GetRotationX(float angle){
//     float cosA = cos(angle);
//     float sinA = sin(angle);
//     return (GetSpeedX() * cosA - GetSpeedY() * sinA);
//
// }
//
// float Ball::GetRotationY(float angle){
//     float cosA = cos(angle);
//     float sinA = sin(angle);
//     return (GetSpeedX() * sinA + GetSpeedY() * cosA);
// }

glm::vec2 Ball::Rotate(const float& angle){
    float cosA = cos(angle);
    float sinA = sin(angle);
    return glm::vec2(
        GetVelocity().x * cosA - GetVelocity().y * sinA, // New X
        GetVelocity().x * sinA + GetVelocity().y * cosA  // New Y
    );
}