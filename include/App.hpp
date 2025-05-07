#ifndef APP_HPP
#define APP_HPP

#include "Ball.hpp"
#include "Character.hpp"
#include "LevelManager.hpp"
#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"
#include "Entity.hpp"
#include "GameText.hpp"
#include "Util/Time.hpp"
#include "Pill.hpp"
#include "Util/SFX.hpp"

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

    void VausHoldBall();

    void ActivateDisruption();

    void DeleteInactiveLasers();

    void DeleteInactiveBall();

    void CheckForCollision();

    void UpdateLivesUI();

    void HandleInput();

    void WhenPlayerLosesBall();

    void ResumePlayerLosesBall();

    void DetectGameOver();

    void Restart(bool reset);

    void InitGame(bool reset);

    glm::vec2 RotateVector(const glm::vec2& vec, float angle);

    void UpdateScoreText();

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
    std::vector<std::shared_ptr<Ball>> m_Balls;
    int m_active_ball_count;

    // Player lives display icon
    std::shared_ptr<Entity> m_Icon;
    // Lives text
    std::shared_ptr<GameText> m_num_of_lives_Text;
    int m_lives;
    int m_old_lives = -1;

    // Pill
    std::shared_ptr<Pill> m_Pill;
    bool isSpawningPill = false;
    bool shouldReplaceVaus = false; // For Blue and Red powerup
    bool otherPowerUp = false; // Except blue and red powerup
    Pill::PILL_TYPE pendingPillType;

    // Bools for developing Green Pill power.
    bool m_has_Glue;
    bool m_ball_Stucked;

    std::vector<std::shared_ptr<Brick>> bricksToRemove;
    int m_level;
    bool m_gameIsRunning;
    bool m_gameOver;
    bool m_ballOutOfBound;

    std::shared_ptr<GameText> m_AnnouncementText;
    std::shared_ptr<Util::SFX> m_GameOverSFX;

    int m_score = 0;
    std::shared_ptr<GameText> m_scoreText;
};

#endif
