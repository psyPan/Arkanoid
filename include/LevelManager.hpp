//
// Created by 潘雙永(HHA) on 2025/3/7.
//

#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP
#include <memory>
#include "BackgroundImage.hpp"
#include "Brick.hpp"
#include "Util/Renderer.hpp"
#include <limits>

class LevelManager{
private:
    std::shared_ptr<BackgroundImage> m_backgroundImage;
    std::vector<std::shared_ptr<Brick>> m_bricks;
    int m_level = 1;
    std::vector<std::vector<Brick::BRICK_TYPE>> m_layout;
    glm::vec2 m_startPos;

public:
    LevelManager(int level);
    // ~LevelManager();

    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() const {
        return m_backgroundImage;
    }

    std::shared_ptr<BackgroundImage> GetBackgroundImage() const {
        return m_backgroundImage;
    }

    int GetLevel() const{
        return m_level;
    }
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level0_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level1_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level2_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level3_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level4_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level5_layout;

    void CreateBrick(Util::Renderer& m_Root);

    std::vector<std::shared_ptr<Brick>>& GetBricks(){
        return m_bricks;
    }

    void SetLevelLayout();

    std::shared_ptr<Brick> PrimaryCollidedBrick(const std::shared_ptr<Ball>& ball);
};

#endif //LEVELMANAGER_HPP
