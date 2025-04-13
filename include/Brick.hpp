//
// Created by 潘雙永(HHA) on 2025/3/19.
//

#ifndef BRICK_HPP
#define BRICK_HPP
#include "Entity.hpp"
#include "Ball.hpp"
#include "Pill.hpp"

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
    explicit Brick(const std::string& ImagePath, Brick::BRICK_TYPE brickType);

    void SetHitCount(int hits) { m_hitCount = hits; }

    void HandleCollisionWithBall(const std::shared_ptr<Ball>& ball);

    void DecreseHitCount(){
        --m_hitCount;
    }

    int GetHitCount() const { return m_hitCount; }

    AABB GetBrickAABB() const;

    // Method to check if the brick is destroyed
    bool IsDestroyed() const {
        return m_isDestroyed;
    }

    BRICK_TYPE GetBrickType() const { return m_brickType; }

    // Method to handle the brick being hit
    void OnHit() {
        // Logic to handle the brick being hit (e.g., mark as destroyed)
        DecreseHitCount();
        if (m_hitCount == 0){
            m_isDestroyed = true;
        }
    }

    float CalculatePenetrationArea(const std::shared_ptr<Ball>& ball);

    glm::vec2 CalculatePenetrationDepth(const std::shared_ptr<Ball>& ball);

    Pill::PILL_TYPE SpawnPill();


private:
    int m_hitCount;
    bool m_isDestroyed = false;
    BRICK_TYPE m_brickType;

};


#endif //BRICK_HPP
