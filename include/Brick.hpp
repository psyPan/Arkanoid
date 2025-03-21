//
// Created by 潘雙永(HHA) on 2025/3/19.
//

#ifndef BRICK_HPP
#define BRICK_HPP
#include "Entity.hpp"
#include "Ball.hpp"

class Brick : public Entity{
public:
    enum class BRICK_TYPE{
        NULL_BRICK,
        GOLD,
        SILVER,
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        LIGHT_BLUE,
        PINK,
        ORANGE,
    };
    explicit Brick(const std::string& ImagePath);

    void SetHitCount(int hits) { m_hitCount = hits; }

    bool CollideWithBall(const std::shared_ptr<Ball>& ball) const;

    void HandleCollisionWithBall(const std::shared_ptr<Ball>& ball);

    void DecreseHitCount() { m_hitCount--; }

    int GetHitCount() const { return m_hitCount; }
private:
    int m_hitCount;
};


#endif //BRICK_HPP
