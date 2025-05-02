#include "LevelManager.hpp"
#include <iostream>
//
// Created by 潘雙永(HHA) on 2025/3/7.
//
std::vector<std::vector<Brick::BRICK_TYPE>> LevelManager::Level0_layout =
    {{Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER},
    {Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED},
    {Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW},
    {Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE},
    {Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK},
    {Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN}
    };

std::vector<std::vector<Brick::BRICK_TYPE>> LevelManager::Level1_layout =
    {{Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK,Brick::BRICK_TYPE::NULL_BRICK},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE},
    {Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::WHITE,Brick::BRICK_TYPE::ORANGE,Brick::BRICK_TYPE::LIGHT_BLUE,Brick::BRICK_TYPE::GREEN},
    {Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::RED}
    };

void SetupBricks(const std::string& path, Brick::BRICK_TYPE brickType, std::vector<std::shared_ptr<Brick>>& m_bricks, Util::Renderer& m_Root,const glm::vec2& start_pos, int i, int j, int hitCount, float spawnProbability = 0.2){
    std::shared_ptr<Brick> brick = std::make_shared<Brick>(path, brickType);
    glm::vec2 update_pos = glm::vec2{start_pos.x + j * brick->GetScaledSize().x, start_pos.y - i * brick->GetScaledSize().y};
    brick->SetHitCount(hitCount);
    brick->SetPosition(update_pos);
    brick->SetZIndex(50);
    m_bricks.push_back(brick);
    m_Root.AddChild(brick);
}

LevelManager::LevelManager(int level) : m_level(level){
    m_backgroundImage = std::make_shared<BackgroundImage>(m_level);
    m_backgroundImage->SetBackGroundImage();
    SetLevelLayout();
}void LevelManager::SetLevelLayout(){
    switch (m_level){
        case 0:
            m_layout = Level0_layout;
            m_startPos.x = 0 - (m_backgroundImage->GetScaledSize().x / 2) + 48;
            m_startPos.y = (m_backgroundImage->GetScaledSize().y / 2 - 24) - ((m_backgroundImage->GetScaledSize().y - 24) / 5) + 20;
            break;
        case 1:
            m_layout = Level1_layout;
            m_startPos.x = 0 - (m_backgroundImage->GetScaledSize().x / 2) + 48;
            m_startPos.y = (m_backgroundImage->GetScaledSize().y / 2 - 24) - ((m_backgroundImage->GetScaledSize().y - 24) / 5) + 65;
            break;
        default:
            m_layout = Level0_layout;
    }
}



std::shared_ptr<Brick> LevelManager::PrimaryCollidedBrick(const std::shared_ptr<Ball>& ball){
    std::shared_ptr<Brick> primaryBrick = nullptr;
    float maxPenetration = 0.0f;
    AABB ballAABB = ball->GetAABB();
    for (auto& brick : m_bricks){
        AABB brickAABB = brick->GetBrickAABB();
        if (ballAABB.Intersects(brickAABB)){
            float penetration = brick->CalculatePenetrationArea(ball);
            if (penetration > maxPenetration){
                maxPenetration = penetration;
                primaryBrick = brick;
            }
        }
    }
    return primaryBrick;
}

void LevelManager::CreateBrick(Util::Renderer& m_Root){
    for (auto i = 0; i < m_layout.size(); i++){
        for (auto j = 0; j < m_layout[0].size(); j++){
            if (m_layout[i][j] == Brick::BRICK_TYPE::SILVER){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/Silver.png";
                SetupBricks(imagePath, Brick::BRICK_TYPE::SILVER, m_bricks, m_Root, m_startPos, i, j, 2);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::GOLD){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Gold.png", Brick::BRICK_TYPE::GOLD);
                m_bricks.push_back(brick);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::RED){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/Red.png";
                SetupBricks(imagePath, Brick::BRICK_TYPE::RED, m_bricks, m_Root, m_startPos, i, j, 1);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::YELLOW){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/Yellow.png";
                SetupBricks(imagePath, Brick::BRICK_TYPE::YELLOW, m_bricks, m_Root, m_startPos, i, j, 1);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::BLUE){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/Blue.png";
                SetupBricks(imagePath, Brick::BRICK_TYPE::BLUE, m_bricks, m_Root, m_startPos, i, j, 1);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::PINK){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/Pink.png";
                SetupBricks(imagePath,Brick::BRICK_TYPE::PINK, m_bricks, m_Root, m_startPos, i, j, 1);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::GREEN){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/Green.png";
                SetupBricks(imagePath,Brick::BRICK_TYPE::GREEN, m_bricks, m_Root, m_startPos, i, j, 1);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::WHITE){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/White.png";
                SetupBricks(imagePath, Brick::BRICK_TYPE::WHITE, m_bricks, m_Root, m_startPos, i, j, 1);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::LIGHT_BLUE){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/LightBlue.png";
                SetupBricks(imagePath, Brick::BRICK_TYPE::LIGHT_BLUE, m_bricks, m_Root, m_startPos, i, j, 1);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::ORANGE){
                std::string imagePath = RESOURCE_DIR"/Image/Brick/Orange.png";
                SetupBricks(imagePath, Brick::BRICK_TYPE::ORANGE, m_bricks, m_Root, m_startPos, i, j, 1);
            }
        }
    }

}
