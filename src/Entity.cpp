//
// Created by 潘雙永(HHA) on 2025/3/9.
//
#include "Entity.hpp"
#include "Util/Image.hpp"


Entity::Entity(const std::string& ImagePath) {
    SetImage(ImagePath);

    ResetPosition();
}

void Entity::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}