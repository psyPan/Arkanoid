//
// Created by 潘雙永(HHA) on 2025/3/8.
//

#include "Character.hpp"
#include <iostream>
#include "Util/Image.hpp"
#include "Util/Renderer.hpp"


Character::Character(const std::string& ImagePath) {
    SetImage(ImagePath);

    ResetPosition();
    lastFireTime = 0.0f;
    m_StartingState = true;
}

void Character::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

// Constants
const float MAX_BOUNCE_ANGLE = M_PI / 1.5; // 60 degrees
void Character::HandleCollisionWithBall(const std::shared_ptr<Ball>& ball) {
    if (!m_StartingState){
        ball->SetVelocity(glm::vec2{ball->GetVelocity().x, -ball->GetVelocity().y});
        // Calculate the relative position of the ball's impact on the paddle
        float relativeIntersectX = (ball->GetPosition().x - GetPosition().x) / GetScaledSize().x;
        // Clamp the value to the range [-1, 1]
        relativeIntersectX = std::max(-1.0f, std::min(1.0f, relativeIntersectX));
        // Calculate the bounce angle
        float bounceAngle = relativeIntersectX * MAX_BOUNCE_ANGLE;

        // Adjust angle
        if (bounceAngle < 0 && bounceAngle > -0.4){
            bounceAngle = -0.4;
        }
        if (bounceAngle > 0 && bounceAngle < 0.4){
            bounceAngle = 0.4;
        }
        bounceAngle = std::max(-1.0f, std::min(1.0f, bounceAngle));
        // Increase speed a little
        float current_speed = glm::length(ball->GetVelocity());
        float new_speed =  1.02 * current_speed;
        if (new_speed > ball->GetMaxSpeed()){
            new_speed = ball->GetMaxSpeed();
        }
        glm::vec2 newVelocity;
        // Calculate the new velocity components
        newVelocity.x = new_speed * std::sin(bounceAngle);
        newVelocity.y = new_speed * std::cos(bounceAngle);

        // Set the new velocity
        ball->SetVelocity(newVelocity);
    }

}

void Character::HandleCollisionWithPill(const std::shared_ptr<Pill>& pill){
    Pill::PILL_TYPE pilltype = pill->GetType();
    switch (pilltype){
        case Pill::PILL_TYPE::BLUE:
            m_PillType = Pill::PILL_TYPE::BLUE;
            break;
        case Pill::PILL_TYPE::GREEN:
            m_PillType = Pill::PILL_TYPE::GREEN;
            break;
        case Pill::PILL_TYPE::RED:
            m_PillType = Pill::PILL_TYPE::RED;
            break;
        case Pill::PILL_TYPE::GREY:
            m_PillType = Pill::PILL_TYPE::GREY;
            break;
        case Pill::PILL_TYPE::PINK:
            m_PillType = Pill::PILL_TYPE::PINK;
            break;
        case Pill::PILL_TYPE::ORANGE:
            m_PillType = Pill::PILL_TYPE::ORANGE;
            break;
        case Pill::PILL_TYPE::LIGHTBLUE:
            m_PillType = Pill::PILL_TYPE::LIGHTBLUE;
            break;
        default:
            m_PillType = Pill::PILL_TYPE::NULL_Pill;
            break;
    }
}

void Character::FireLaser(double currentTime, Util::Renderer& m_Root){
    if (currentTime - lastFireTime >= 150){
        std::shared_ptr<Laser> laser1 = std::make_shared<Laser>(RESOURCE_DIR"/Image/Laser/Laser.png", glm::vec2{GetPosition().x - GetScaledSize().x/4, GetPosition().y + GetScaledSize().y/2}, 10);
        std::shared_ptr<Laser> laser2 = std::make_shared<Laser>(RESOURCE_DIR"/Image/Laser/Laser.png", glm::vec2{GetPosition().x + GetScaledSize().x/4, GetPosition().y + GetScaledSize().y/2}, 10);
        laser1->SetVisible(true);
        laser1->SetZIndex(50);
        laser2->SetVisible(true);
        laser2->SetZIndex(50);
        m_Lasers.push_back(laser1);
        m_Lasers.push_back(laser2);
        lastFireTime = currentTime;
        m_Root.AddChild(laser1);
        m_Root.AddChild(laser2);
    }
}

