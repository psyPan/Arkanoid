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
    BackgroundImage() : GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Image/Background/Level1.png"), -10) {

    }
    void NextLevel(const int level) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(ImagePath(level));
    }



private:
    inline std::string ImagePath(const int level) {
        return RESOURCE_DIR"/Image/Background/level" + std::to_string(level) + ".png";
    }
};


#endif //BACKGROUND_HPP
