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
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level6_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level7_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level8_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level9_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level10_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level11_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level12_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level13_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level14_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level15_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level16_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level17_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level18_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level19_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level20_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level21_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level22_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level23_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level24_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level25_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level26_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level27_layout;
    static std::vector<std::vector<Brick::BRICK_TYPE>> Level28_layout;

    void CreateBrick(Util::Renderer& m_Root);

    std::vector<std::shared_ptr<Brick>>& GetBricks(){
        return m_bricks;
    }

    void SetLevelLayout();

    std::shared_ptr<Brick> PrimaryCollidedBrick(const std::shared_ptr<Ball>& ball);
};

#endif //LEVELMANAGER_HPP
