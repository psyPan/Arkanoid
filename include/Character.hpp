//
// Created by 潘雙永(HHA) on 2025/3/8.
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"
#include "Ball.hpp"

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

    // TODO: Implement the collision detection
    bool CollideWithBall(const std::shared_ptr<Ball>& ball) const;
        // Get Vaus (Paddle) Bounding Box
        // float vausLeft   = GetPosition().x - GetScaledSize().x / 2;
        // float vausRight  = GetPosition().x + GetScaledSize().x / 2;
        // float vausTop    = GetPosition().y + GetScaledSize().y / 2;
        // float vausBottom = GetPosition().y - GetScaledSize().y / 2;
        //
        // // Get Ball Bounding Box
        // float ballLeft   = ball->GetPosition().x - ball->GetScaledSize().x / 2;
        // float ballRight  = ball->GetPosition().x + ball->GetScaledSize().x / 2;
        // float ballTop    = ball->GetPosition().y + ball->GetScaledSize().y / 2;
        // float ballBottom = ball->GetPosition().y - ball->GetScaledSize().y / 2;
        //
        // // AABB Collision Check
        // bool isColliding = (vausRight > ballLeft && vausLeft < ballRight &&
        //                     vausTop > ballBottom && vausBottom < ballTop);
        //
        // return isColliding;


    void HandleCollisionWithBall(const std::shared_ptr<Ball>& ball);



    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};



#endif //CHARACTER_HPP
