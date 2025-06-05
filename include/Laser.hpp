//
// Created by 潘雙永(HHA) on 2025/4/12.
//

#ifndef LASER_HPP
#define LASER_HPP
#include "Entity.hpp"

class Laser: public Entity{
public:
    explicit Laser(const std::string& imagePath, const glm::vec2& pos, float speed, int trajectory);

    void Update(const glm::vec2& screenSize);

    void SetDirection(const glm::vec2& direction){ m_direction_unit_vector = direction; };
    bool IsActive() const{
        return active;
    };
    void SetActive(bool a){
        active = a;
    }
private:
    float m_speed;
    bool active;
    int m_trajectory;
    glm::vec2 m_direction_unit_vector;
};

#endif //LASER_HPP
