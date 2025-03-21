#include "LevelManager.hpp"
#include <iostream>
//
// Created by 潘雙永(HHA) on 2025/3/7.
//
std::vector<std::vector<Brick::BRICK_TYPE>> LevelManager::Level1_layout =
    {{Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER,Brick::BRICK_TYPE::SILVER},
    {Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED,Brick::BRICK_TYPE::RED},
    {Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW,Brick::BRICK_TYPE::YELLOW},
    {Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE,Brick::BRICK_TYPE::BLUE},
    {Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK,Brick::BRICK_TYPE::PINK},
    {Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN,Brick::BRICK_TYPE::GREEN}
    };

LevelManager::LevelManager() : m_level(1){
    m_backgroundImage = std::make_shared<BackgroundImage>();
    SetLevelLayout();

}

void LevelManager::NextLevel() {
    // if (m_Phase == 7) return;
    // LOG_DEBUG("Passed! Next phase: {}", m_Phase);
    m_backgroundImage->NextLevel(m_level);
    // m_TaskText->NextPhase(m_Phase++);
}

void LevelManager::SetLevelLayout(){
    switch (m_level){
        case 1:
            m_layout = Level1_layout;
            break;
        default:
            m_layout = Level1_layout;
    }
}

void LevelManager::CreateBrick(Util::Renderer& m_Root){
    for (auto i = 0; i < m_layout.size(); i++){
        for (auto j = 0; j < m_layout[0].size(); j++){
            glm::vec2 start_pos;
            start_pos.x = 0 - (m_backgroundImage->GetScaledSize().x / 2) + 48;
            start_pos.y = (m_backgroundImage->GetScaledSize().y / 2 - 24) - ((m_backgroundImage->GetScaledSize().y - 24) / 5) + 20;
            if (m_layout[i][j] == Brick::BRICK_TYPE::SILVER){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Silver.png");
                glm::vec2 update_pos;
                update_pos.x = start_pos.x + j * brick->GetScaledSize().x;
                update_pos.y = start_pos.y - i * brick->GetScaledSize().y;
                brick->SetHitCount(2);
                brick->SetPosition(update_pos);
                m_bricks.push_back(brick);
                m_Root.AddChild(brick);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::GOLD){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Gold.png");
                m_bricks.push_back(brick);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::RED){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Red.png");
                glm::vec2 update_pos;
                update_pos.x = start_pos.x + j * brick->GetScaledSize().x;
                update_pos.y = start_pos.y - i * brick->GetScaledSize().y;
                brick->SetHitCount(1);
                brick->SetPosition(update_pos);
                m_bricks.push_back(brick);
                m_Root.AddChild(brick);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::YELLOW){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Yellow.png");
                glm::vec2 update_pos;
                update_pos.x = start_pos.x + j * brick->GetScaledSize().x;
                update_pos.y = start_pos.y - i * brick->GetScaledSize().y;
                brick->SetHitCount(1);
                brick->SetPosition(update_pos);
                m_bricks.push_back(brick);
                m_Root.AddChild(brick);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::BLUE){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Blue.png");
                glm::vec2 update_pos;
                update_pos.x = start_pos.x + j * brick->GetScaledSize().x;
                update_pos.y = start_pos.y - i * brick->GetScaledSize().y;
                brick->SetHitCount(1);
                brick->SetPosition(update_pos);
                m_bricks.push_back(brick);
                m_Root.AddChild(brick);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::PINK){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Pink.png");
                glm::vec2 update_pos;
                update_pos.x = start_pos.x + j * brick->GetScaledSize().x;
                update_pos.y = start_pos.y - i * brick->GetScaledSize().y;
                brick->SetHitCount(1);
                brick->SetPosition(update_pos);
                m_bricks.push_back(brick);
                m_Root.AddChild(brick);
            }
            else if (m_layout[i][j] == Brick::BRICK_TYPE::GREEN){
                std::shared_ptr<Brick> brick = std::make_shared<Brick>(RESOURCE_DIR"/Image/Brick/Green.png");
                glm::vec2 update_pos;
                update_pos.x = start_pos.x + j * brick->GetScaledSize().x;
                update_pos.y = start_pos.y - i * brick->GetScaledSize().y;
                brick->SetHitCount(1);
                brick->SetPosition(update_pos);
                m_bricks.push_back(brick);
                m_Root.AddChild(brick);
            }
        }
    }

}
