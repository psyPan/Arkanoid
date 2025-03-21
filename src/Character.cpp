//
// Created by 潘雙永(HHA) on 2025/3/8.
//

#include "Character.hpp"
#include <ostream>
#include "Util/Image.hpp"


Character::Character(const std::string& ImagePath) {
    SetImage(ImagePath);

    ResetPosition();
}

void Character::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

bool Character::CollideWithBall(const std::shared_ptr<Ball>& ball) const{
    // Get Vaus (Paddle) Bounding Box
    float vausLeft   = GetPosition().x - GetScaledSize().x / 2;
    float vausRight  = GetPosition().x + GetScaledSize().x / 2;
    float vausTop    = GetPosition().y + GetScaledSize().y / 2;
    float vausBottom = GetPosition().y - GetScaledSize().y / 2;

    // Get Ball Bounding Box
    float ballLeft   = ball->GetPosition().x - ball->GetScaledSize().x / 2;
    float ballRight  = ball->GetPosition().x + ball->GetScaledSize().x / 2;
    float ballTop    = ball->GetPosition().y + ball->GetScaledSize().y / 2;
    float ballBottom = ball->GetPosition().y - ball->GetScaledSize().y / 2;

    // AABB Collision Check
    bool isColliding = (vausRight > ballLeft && vausLeft < ballRight &&
                        vausTop > ballBottom && vausBottom < ballTop);

    return isColliding;

}

// Constants
const float MAX_BOUNCE_ANGLE = M_PI / 1.5; // 60 degrees


void Character::HandleCollisionWithBall(const std::shared_ptr<Ball>& ball) {
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

    // Increase speed a little
    float current_speed = glm::length(ball->GetVelocity());
    float new_speed =  1.1 * current_speed;
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
