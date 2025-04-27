//
// Created by 潘雙永(HHA) on 2025/4/23.
//

#ifndef GAMETEXT_HPP
#define GAMETEXT_HPP
#include "Util/GameObject.hpp"

class GameText: public Util::GameObject{
public:
    GameText(std::string text, glm::vec2 pos, int fontsize);

    void ChangeText(const std::string text);

    void SetPosition(glm::vec2 pos);
private:
};

#endif //GAMETEXT_HPP
