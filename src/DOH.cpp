//
// Created by 潘雙永(HHA) on 2025/6/5.
//
#include "DOH.hpp"
#include <ostream>
void ReflectVectorV(const glm::vec2& ballVel, const glm::vec2& normalVector, glm::vec2& newVelocity){
    glm::vec2 ballDirection = glm::normalize(ballVel);
    float speed = glm::length(ballVel);
    float dot_product = glm::dot(ballDirection, normalVector);
    glm::vec2 reflectionVector = ballDirection - 2 * dot_product * normalVector; // law of reflection formula
    newVelocity = reflectionVector * speed;
}


DOH::DOH(const std::string& ImagePath): Character(ImagePath){
    m_get_attacked_sound = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/DOH_got_attacked.wav");
    m_DOH_laser_sound = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/DOH_laser.wav");
}

void DOH::FireLaser(double currentTime, Util::Renderer& m_Root, const std::shared_ptr<Character>& vaus){
    m_DOH_laser_sound->Play();
    std::shared_ptr<Laser> laser = std::make_shared<Laser>(RESOURCE_DIR"/Image/DOH/DOH_laser.png", glm::vec2{GetPosition().x, GetPosition().y - 10}, 6, -1);
    laser->SetDirection(glm::normalize(GetPosition() - vaus->GetPosition()));
    laser->SetVisible(true);
    laser->SetZIndex(50);
    m_Lasers.push_back(laser);
    m_lastFireTime = currentTime;
    m_Root.AddChild(laser);
}

void DOH::HandleCollisionWithBall(const std::shared_ptr<Ball>& ball){
    m_get_attacked_sound->Play();

    glm::vec2 ballVel = ball->GetVelocity();
    glm::vec2 newVelocity = glm::vec2{0,0};

    glm::vec2 diff = ball->GetPosition() - GetPosition();
    float overlapX = (ball->GetScaledSize().x + GetScaledSize().x) / 2.0f - std::abs(diff.x);
    float overlapY = (ball->GetScaledSize().y + GetScaledSize().y) / 2.0f - std::abs(diff.y);

    if (overlapX > overlapY) { // Hitting the horizontal plane of brick
        glm::vec2 newPos = ball->GetPosition();
        newPos.y += (diff.y > 0 ? 1 : -1) * overlapY;
        ball->SetPosition(newPos);
        if (diff.y < 0) {
            glm::vec2 normalVector = glm::vec2{0,-1};
            ReflectVectorV(ballVel, normalVector, newVelocity);

        } else {
            glm::vec2 normalVector = glm::vec2{0,1};
            ReflectVectorV(ballVel, normalVector, newVelocity);
        }
    } else {
        glm::vec2 newPos = ball->GetPosition();
        // newPos.x += (diff.x > 0 ? 1 : -1) * overlapX;
        ball->SetPosition(newPos);
        if (diff.x > 0) {
            glm::vec2 normalVector = glm::vec2{1,0};
            ReflectVectorV(ballVel, normalVector, newVelocity);
        } else {
            glm::vec2 normalVector = glm::vec2{-1,0};
            ReflectVectorV(ballVel, normalVector, newVelocity);
        }
    }
    ball->SetVelocity(newVelocity);
}

