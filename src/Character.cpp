//
// Created by 潘雙永(HHA) on 2025/3/8.
//

#include "Character.hpp"

#include <iostream>
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

void Character::HandleCollisionWithBall(const std::shared_ptr<Ball>& ball){
    // Simple bounce
    ball->SetVelocity(glm::vec2{ball->GetVelocity().x, -ball->GetVelocity().y});
    float relative_pos_x = ball->GetPosition().x - GetPosition().x;
    std::cout << "relative_pos_x: " << relative_pos_x << std::endl;
    float coeff = relative_pos_x / GetScaledSize().x;
    std::cout << "coeff: " << coeff << std::endl;
    float angle = coeff * (M_PI / 2.4);
    std::cout << "Before rotate: " << std::endl;
    std::cout << "Velocity X " <<ball->GetVelocity().x << std::endl;
    std::cout << "Velocity Y " <<ball->GetVelocity().y << std::endl;
    ball->SetVelocity(ball->Rotate(angle));
    std::cout << "Velocity X " <<ball->GetVelocity().x << std::endl;
    std::cout << "Velocity Y " <<ball->GetVelocity().y << std::endl;
}
