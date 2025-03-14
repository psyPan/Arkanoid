#include "LevelManager.hpp"
#include <iostream>
//
// Created by 潘雙永(HHA) on 2025/3/7.
//
LevelManager::LevelManager(){
    m_backgroundImage = std::make_shared<BackgroundImage>();

}

void LevelManager::NextLevel() {
    // if (m_Phase == 7) return;
    // LOG_DEBUG("Passed! Next phase: {}", m_Phase);
    m_backgroundImage->NextLevel(m_level);
    // m_TaskText->NextPhase(m_Phase++);
}