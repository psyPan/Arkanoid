//
// Created by 潘雙永(HHA) on 2025/3/28.
//

#ifndef PILL_HPP
#define PILL_HPP
#include "Entity.hpp"

class Pill : public Entity{
public:
    enum class PILL_TYPE{
        NULL_Pill,
        BLUE,
        LIGHTBLUE,
        GREEN,
        RED,
        ORANGE,
        PINK,
        GREY,
    };
    Pill(const std::string& imagePath, const PILL_TYPE& type, const glm::vec2 pos);

    glm::vec2 GetVelocity() const { return m_velocity; }

    void SetVelocity(const glm::vec2& velocity) {m_velocity = velocity;}

    Pill::PILL_TYPE GetType() const { return m_type; }

private:
    PILL_TYPE m_type;
    glm::vec2 m_velocity = glm::vec2{0};
};

#endif //PILL_HPP
