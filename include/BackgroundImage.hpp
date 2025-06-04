//
// Created by 潘雙永(HHA) on 2025/3/7.
//

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <iostream>
class BackgroundImage : public Util::GameObject{
public:
    BackgroundImage(int level) : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/Level0.png"), -10), m_level(level) {

    }
    void SetBackGroundImage() {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(RESOURCE_DIR"/Image/Background/level" + std::to_string(m_level % 3) + ".png");
    }

    void SetFinalBackgroundImage(){
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(RESOURCE_DIR"/Image/Background/final.png");
    }


private:
    int m_level;
};


#endif //BACKGROUND_HPP
