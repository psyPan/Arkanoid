//
// Created by 潘雙永(HHA) on 2025/3/10.
//

#ifndef BALL_HPP
#define BALL_HPP

#include "Entity.hpp"

class Ball : public Entity{
private:
    bool m_isSticky;
    glm::vec2 m_velocity = glm::vec2{0,0};
    float m_maxSpeed;
    float m_minSpeed;

public:
    explicit Ball(const std::string& ImagePath, const bool& IsSticky, const glm::vec2& velocity)
        : Entity(ImagePath), m_isSticky(IsSticky), m_velocity(velocity), m_maxSpeed(625.0f), m_minSpeed(80.0f) {};

    bool IsSticky() const { return m_isSticky; }

    void SetIsSticky(const bool& IsSticky) { m_isSticky = IsSticky; }

    glm::vec2 GetVelocity() const { return m_velocity; }

    void SetVelocity(const glm::vec2& velocity) {m_velocity = velocity;}

    float GetMaxSpeed() const { return m_maxSpeed; }

    float GetMinSpeed() const { return m_minSpeed; }

    void SlowDownSpeed();

};

#endif //BALL_HPP
