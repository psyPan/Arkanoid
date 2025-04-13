//
// Created by 潘雙永(HHA) on 2025/3/8.
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Ball.hpp"
#include "Laser.hpp"
#include "Pill.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void HandleCollisionWithBall(const std::shared_ptr<Ball>& ball);

    Pill::PILL_TYPE GetCurrentPill() const { return m_PillType; }

    void SetCurrentPill(Pill::PILL_TYPE pillType) { m_PillType = pillType; }

    void HandleCollisionWithPill(const std::shared_ptr<Pill>& pill);

    void FireLaser(double currentTime, Util::Renderer& m_Root);

    std::vector<std::shared_ptr<Laser>> GetLasers() { return m_Lasers; }

    AABB GetAABB() const {
        float halfWidth = GetScaledSize().x / 2.0f;
        float halfHeight = GetScaledSize().y / 2.0f;
        return AABB(GetPosition().x - halfWidth, GetPosition().x + halfWidth,
                    GetPosition().y + halfHeight, GetPosition().y - halfHeight);
    }

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
    Pill::PILL_TYPE m_PillType = Pill::PILL_TYPE::NULL_Pill;
    std::vector<std::shared_ptr<Laser>> m_Lasers;
    double lastFireTime = 0;
};



#endif //CHARACTER_HPP
