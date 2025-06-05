//
// Created by 潘雙永(HHA) on 2025/6/5.
//

#ifndef DOH_HPP
#define DOH_HPP
#include "Character.hpp"
#include "Laser.hpp"

class DOH: public Character{
public:
    explicit DOH(const std::string& ImagePath);
    void FireLaser(double currentTime, Util::Renderer& m_Root, const std::shared_ptr<Character>& vaus);
private:
    std::string m_ImagePath;
    double m_lastFireTime = 0;
};

#endif //DOH_HPP
