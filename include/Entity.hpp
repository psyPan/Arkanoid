//
// Created by 潘雙永(HHA) on 2025/3/9.
//

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include "Util/GameObject.hpp"

class Entity : public Util::GameObject{
private:
    std::string m_ImagePath;
    void ResetPosition() { m_Transform.translation = {0, 0}; }

public:
    explicit Entity(const std::string& ImagePath);

    Entity(const Entity&) = delete;

    Entity(Entity&&) = delete;

    Entity& operator=(const Entity&) = delete;

    Entity& operator=(Entity&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

};

#endif //ENTITY_HPP
