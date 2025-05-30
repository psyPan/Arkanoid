//
// Created by 潘雙永(HHA) on 2025/3/19.
//
#include "Brick.hpp"

#include <iostream>
#include <random>

void ReflectVector(const glm::vec2& ballVel, const glm::vec2& normalVector, glm::vec2& newVelocity){
    glm::vec2 ballDirection = glm::normalize(ballVel);
    float speed = glm::length(ballVel);
    float dot_product = glm::dot(ballDirection, normalVector);
    glm::vec2 reflectionVector = ballDirection - 2 * dot_product * normalVector; // law of reflection formula
    newVelocity = reflectionVector * speed;
}

Brick::Brick(const std::string& ImagePath,Brick::BRICK_TYPE brickType, int point) : Entity(ImagePath), m_brickType(brickType), m_point(point) {
    SetVisible(true);
    SetZIndex(50);
    m_BrickBallSound = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/Brick_Ball_Touched.wav");
}

void Brick::HandleCollisionWithBall(const std::shared_ptr<Ball>& ball) {
    m_BrickBallSound->Play();

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
            ReflectVector(ballVel, normalVector, newVelocity);

        } else {
            glm::vec2 normalVector = glm::vec2{0,1};
            ReflectVector(ballVel, normalVector, newVelocity);
        }
    } else {
        glm::vec2 newPos = ball->GetPosition();
        newPos.x += (diff.x > 0 ? 1 : -1) * overlapX;
        ball->SetPosition(newPos);
        if (diff.x > 0) {
            glm::vec2 normalVector = glm::vec2{1,0};
            ReflectVector(ballVel, normalVector, newVelocity);
        } else {
            glm::vec2 normalVector = glm::vec2{-1,0};
            ReflectVector(ballVel, normalVector, newVelocity);
        }
    }
    ball->SetVelocity(newVelocity);
}

AABB Brick::GetBrickAABB() const{
    float halfWidth = GetScaledSize().x / 2.0f;
    float halfHeight = GetScaledSize().y / 2.0f;
    return AABB(GetPosition().x - halfWidth, GetPosition().x + halfWidth,
                GetPosition().y + halfHeight, GetPosition().y - halfHeight);
}

float Brick::CalculatePenetrationArea(const std::shared_ptr<Ball>& ball){
    float overlapX = std::min(ball->GetAABB().right, GetBrickAABB().right) - std::max(ball->GetAABB().left, GetBrickAABB().left);
    float overlapY = std::min(ball->GetAABB().top, GetBrickAABB().top) - std::max(ball->GetAABB().bottom, GetBrickAABB().bottom);
    if (overlapX > 0 && overlapY > 0){
        return overlapX * overlapY; // Area of overlap
    }
    return 0.0f; // No overlap
}

glm::vec2 Brick::CalculatePenetrationDepth(const std::shared_ptr<Ball>& ball){
    AABB ballAABB = ball->GetAABB();
    AABB brickAABB = GetBrickAABB();

    float penetrationX = std::min(brickAABB.right - ballAABB.left, ballAABB.right - brickAABB.left);
    float penetrationY = std::min(brickAABB.top - ballAABB.bottom, ballAABB.top - brickAABB.bottom);

    return glm::vec2(penetrationX, penetrationY);
}

Pill::PILL_TYPE Brick::SpawnPill(){
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);
    double randomValue = dis(gen);
    // Define the probabilities
    const double p_blue = 0.25;
    const double p_red = 0.25;
    const double p_light_blue = 0.2;
    const double p_green = 0.1;
    const double p_orange = 0.1;
    const double p_gray = 0.05;
    const double p_pink = 0.05;

    if (randomValue < p_blue){
        return Pill::PILL_TYPE::BLUE;
    }
    else if (randomValue < p_blue + p_red) {
        return Pill::PILL_TYPE::RED;
    } else if (randomValue < p_blue + p_red + p_light_blue) {
        return Pill::PILL_TYPE::LIGHTBLUE;
    } else if (randomValue < p_blue + p_red + p_light_blue + p_green) {
        return Pill::PILL_TYPE::GREEN;
    } else if (randomValue < p_blue + p_red + p_light_blue + p_green + p_orange) {
        return Pill::PILL_TYPE::ORANGE;
    } else if (randomValue < p_blue + p_red + p_light_blue + p_green + p_orange + p_gray) {
        return Pill::PILL_TYPE::GREY;
    } else {
        return Pill::PILL_TYPE::PINK;
    }
}



