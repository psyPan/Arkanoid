//
// Created by 潘雙永(HHA) on 2025/4/23.
//
#include "GameText.hpp"

#include "Util/Text.hpp"

GameText::GameText(std::string text, glm::vec2 pos, int fontsize) : GameObject(std::make_unique<Util::Text>(RESOURCE_DIR"/Font/BruceForeverRegular.ttf",
                                                fontsize, text,
                                                    Util::Color::FromName(Util::Colors::WHITE)), 100)
{
    m_Transform.translation = pos;
}

void GameText::ChangeText(const std::string text){
    auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
    temp->SetText(text);
}

void GameText::SetPosition(glm::vec2 pos){
    m_Transform.translation = pos;
}
