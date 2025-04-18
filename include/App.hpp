#ifndef APP_HPP
#define APP_HPP

#include "Ball.hpp"
#include "Character.hpp"
#include "LevelManager.hpp"
#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"
#include "Entity.hpp"
#include "Util/Time.hpp"
#include "Pill.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    void SetSpawningState(bool isSpawningPill) { this->isSpawningPill = isSpawningPill; }

    bool IsSpawningPill() { return isSpawningPill; }

    void CreatePill(const Pill::PILL_TYPE& pill, const glm::vec2& pos);

    void VausPowerUp();

    void OtherPowerUp();

    void DeleteInactiveLasers();

    void CheckForCollision();

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;

    // LevelManager
    std::shared_ptr<LevelManager> m_LevelManager;

    Util::Renderer m_Root;
    Util::Time m_Time;

    // Character
    std::shared_ptr<Character> m_Vaus;

    // Entity
    std::shared_ptr<Ball> m_Ball;

    // Pill
    std::shared_ptr<Pill> m_Pill;
    bool isSpawningPill = false;
    bool shouldReplaceVaus = false; // For Blue and Red powerup
    bool otherPowerUp = false; // Except blue and red powerup
    Pill::PILL_TYPE pendingPillType;
    std::vector<std::shared_ptr<Brick>> bricksToRemove;
    int m_level;
};

#endif
