//
// Created by 潘雙永(HHA) on 2025/3/7.
//

#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP
#include <memory>

#include "BackgroundImage.hpp"

class LevelManager{
private:
    std::shared_ptr<BackgroundImage> m_backgroundImage;
    int m_level = 1;

    public:
    LevelManager();
    // ~LevelManager();
    void NextLevel();

    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() const {
        return m_backgroundImage;
    }

    std::shared_ptr<BackgroundImage> GetBackgroundImage() const {
        return m_backgroundImage;
    }
};

#endif //LEVELMANAGER_HPP
