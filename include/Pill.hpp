//
// Created by 潘雙永(HHA) on 2025/3/28.
//

#ifndef PILL_HPP
#define PILL_HPP
#include "Entity.hpp"
#include "Brick.hpp"
#include "Character.hpp"

class Pill : public Entity{
public:
    enum class PILL_TYPE{
        BLUE,
        LIGHTBLUE,
        GREEN,
        RED,
        YELLOW,
        PINK,
        GREY,
    };
    bool CollideWithVaus(const std::shared_ptr<Character>& vaus) const;

};

#endif //PILL_HPP
