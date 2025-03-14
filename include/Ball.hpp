//
// Created by 潘雙永(HHA) on 2025/3/10.
//

#ifndef BALL_HPP
#define BALL_HPP

#include "Entity.hpp"


class Ball : public Entity{
private:
    bool m_isSticky;
    glm::vec2 m_velocity;

public:
    explicit Ball(const std::string& ImagePath, const bool& IsSticky, const glm::vec2& velocity)
        : Entity(ImagePath), m_isSticky(IsSticky), m_velocity(velocity) {};

    bool IsSticky() const { return m_isSticky; }

    void SetIsSticky(const bool& IsSticky) { m_isSticky = IsSticky; }

    glm::vec2 GetVelocity() const { return m_velocity; }

    void SetVelocity(const glm::vec2& velocity) {m_velocity = velocity;}

    glm::vec2 Rotate(const float& angle);

    // void IncreaseVelocity(const float& Increase) {m_velocity += Increase;}
    //
    // void DecreaseSpeedX(const float& SpeedX) { m_SpeedX -= SpeedX; }
    // void DecreaseSpeedY(const float& SpeedY) { m_SpeedY -= SpeedY; }
    //
    // float GetRotationX(float angle);
    // float GetRotationY(float angle);

};

#endif //BALL_HPP
