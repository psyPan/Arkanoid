//
// Created by 潘雙永(HHA) on 2025/3/9.
//

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "Util/GameObject.hpp"

struct AABB {
    float left;   // The x-coordinate of the left edge
    float right;  // The x-coordinate of the right edge
    float top;    // The y-coordinate of the top edge
    float bottom; // The y-coordinate of the bottom edge

    // Constructor to initialize the AABB
    AABB(float l, float r, float t, float b)
        : left(l), right(r), top(t), bottom(b) {}

    // Method to check if this AABB intersects with another AABB
    bool Intersects(const AABB& other) const {
        return !(right < other.left || left > other.right ||
                 top < other.bottom || bottom > other.top);
    }
};

class Entity : public Util::GameObject{
private:
    std::string m_ImagePath;
    void ResetPosition() { m_Transform.translation = {0, 0}; }

public:
    Entity(const std::string& ImagePath);

    Entity(const Entity&) = delete;

    Entity(Entity&&) = delete;

    Entity& operator=(const Entity&) = delete;

    Entity& operator=(Entity&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    AABB GetAABB() const {
        float halfWidth = GetScaledSize().x / 2.0f;
        float halfHeight = GetScaledSize().y / 2.0f;
        return AABB(GetPosition().x - halfWidth, GetPosition().x + halfWidth,
                    GetPosition().y + halfHeight, GetPosition().y - halfHeight);
    }

};

#endif //ENTITY_HPP
