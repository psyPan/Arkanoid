//
// Created by 潘雙永(HHA) on 2025/4/24.
//
#include "Ball.hpp"

void Ball::SlowDownSpeed(){
    glm::vec2 ballVel = GetVelocity();
    float current_speed = glm::length(ballVel);
    float new_speed =  0.75 * current_speed;
    if (new_speed < GetMinSpeed()){
        new_speed = GetMinSpeed();
    }
    glm::vec2 newVelocity = glm::normalize(ballVel) * new_speed;
    SetVelocity(newVelocity);
}

void Ball::MaximizeSpeed(){
    SetVelocity(normalize(GetVelocity()) * m_maxSpeed);
}
