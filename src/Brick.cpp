//
// Created by 潘雙永(HHA) on 2025/3/19.
//
#include "Brick.hpp"
#include <random>
Brick::Brick(const std::string& ImagePath) : Entity(ImagePath){
    SetVisible(true);
    SetZIndex(5);
}

bool Brick::CollideWithBall(const std::shared_ptr<Ball>& ball) const{
    // Get Vaus (Paddle) Bounding Box
    float brickLeft   = GetPosition().x - GetScaledSize().x / 2;
    float brickRight  = GetPosition().x + GetScaledSize().x / 2;
    float brickTop    = GetPosition().y + GetScaledSize().y / 2;
    float brickBottom = GetPosition().y - GetScaledSize().y / 2;

    // Get Ball Bounding Box
    float ballLeft   = ball->GetPosition().x - ball->GetScaledSize().x / 2;
    float ballRight  = ball->GetPosition().x + ball->GetScaledSize().x / 2;
    float ballTop    = ball->GetPosition().y + ball->GetScaledSize().y / 2;
    float ballBottom = ball->GetPosition().y - ball->GetScaledSize().y / 2;

    // AABB Collision Check
    bool isColliding = (brickRight >= ballLeft && brickLeft <= ballRight &&
                        brickTop >= ballBottom && brickBottom <= ballTop);

    return isColliding;
}

const float MAX_BOUNCE_ANGLE = M_PI / 2.5; // 60 degrees


void Brick::HandleCollisionWithBall(const std::shared_ptr<Ball>& ball) {
    ball->SetVelocity(glm::vec2{ball->GetVelocity().x, - ball->GetVelocity().y});
    // Calculate the relative position of the ball's impact on the brick
    float relativeIntersectX = (GetPosition().x - ball->GetPosition().x) / GetScaledSize().x;
    // Clamp the value to the range [-1, 1]
    relativeIntersectX = std::max(-1.0f, std::min(1.0f, relativeIntersectX));
    // Calculate the bounce angle
    float bounceAngle = relativeIntersectX * MAX_BOUNCE_ANGLE;

    // Adjust angle
    if (bounceAngle < 0 && bounceAngle > -0.2){
        bounceAngle = -0.2;
    }
    if (bounceAngle > 0 && bounceAngle < 0.2){
        bounceAngle = 0.2;
    }

    // Increase speed a little
    float current_speed = glm::length(ball->GetVelocity());
    float new_speed =  1.05 * current_speed;
    if (new_speed > ball->GetMaxSpeed()){
        new_speed = ball->GetMaxSpeed();
    }
    glm::vec2 newVelocity;
    // Calculate the new velocity components
    newVelocity.x = - new_speed * std::sin(bounceAngle);
    newVelocity.y = - new_speed * std::cos(bounceAngle);

    // Set the new velocity
    ball->SetVelocity(newVelocity);
}

bool Brick::ShouldSpawnPowerUp(double spawnProbability){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen) < spawnProbability;
}

AABB Brick::GetBrickAABB() const{
    float halfWidth = GetScaledSize().x / 2.0f;
    float halfHeight = GetScaledSize().y / 2.0f;
    return AABB(GetPosition().x - halfWidth, GetPosition().x + halfWidth,
                GetPosition().y + halfHeight, GetPosition().y - halfHeight);
}

float Brick::CalculatePenetrationDepth(const std::shared_ptr<Ball>& ball){
    float overlapX = std::min(ball->GetAABB().right, GetBrickAABB().right) - std::max(ball->GetAABB().left, GetBrickAABB().left);
    float overlapY = std::min(ball->GetAABB().top, GetBrickAABB().top) - std::max(ball->GetAABB().bottom, GetBrickAABB().bottom);
    if (overlapX > 0 && overlapY > 0){
        return overlapX * overlapY; // Area of overlap
    }
    return 0.0f; // No overlap
}

