//
// Created by 潘雙永(HHA) on 2025/3/28.
//
#include "Pill.hpp"


Pill::Pill(const std::string& imagePath, const Pill::PILL_TYPE& pill, const glm::vec2 pos): Entity(imagePath), m_type(pill) {
    SetPosition(pos);
    SetVelocity({0,-50});
    SetVisible(true);
    SetZIndex(5);
}



