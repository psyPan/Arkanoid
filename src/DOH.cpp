//
// Created by 潘雙永(HHA) on 2025/6/5.
//
#include "DOH.hpp"

#include <iostream>
#include <ostream>

DOH::DOH(const std::string& ImagePath): Character(ImagePath){

}

void DOH::FireLaser(double currentTime, Util::Renderer& m_Root, const std::shared_ptr<Character>& vaus){
    std::shared_ptr<Laser> laser = std::make_shared<Laser>(RESOURCE_DIR"/Image/Laser/DOH_laser.png", glm::vec2{GetPosition().x, GetPosition().y - 10}, 6, -1);
    laser->SetDirection(glm::normalize(GetPosition() - vaus->GetPosition()));
    laser->SetVisible(true);
    laser->SetZIndex(50);
    m_Lasers.push_back(laser);
    m_lastFireTime = currentTime;
    m_Root.AddChild(laser);
}
