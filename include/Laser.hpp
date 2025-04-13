//
// Created by 潘雙永(HHA) on 2025/4/12.
//

#ifndef LASER_HPP
#define LASER_HPP
#include "Entity.hpp"

class Laser: public Entity{
public:
    explicit Laser(const std::string& imagePath, const glm::vec2& pos, float speed);
    void Update();
private:
    float m_speed;
};

#endif //LASER_HPP
