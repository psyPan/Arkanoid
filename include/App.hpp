#ifndef APP_HPP
#define APP_HPP

#include "Ball.hpp"
#include "Character.hpp"
#include "DOH.hpp"
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

    bool AllBrickIsGold();

    void DOH_FiringLasers();

    void DOH_HealthBar_Manager();

    void Game_Winning_Manager();

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

    std::shared_ptr<DOH> m_DOH = nullptr;
    std::shared_ptr<Entity> m_DOH_health_bar = nullptr;
    std::shared_ptr<Entity> m_DOH_Frame = nullptr;

    int m_DOH_laser_counter = 0;
    double m_DOH_last_laser_time = 0.0;
    double m_DOH_last_laser_set_time = 0.0;
    bool m_DOH_is_firing = true;
    int m_DOH_HP = 100;
    bool m_Vaus_get_hit = false;

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
    int m_level = 0;
    bool m_gameIsRunning;
    bool m_gameOver;
    bool m_ballOutOfBound;

    std::shared_ptr<GameText> m_AnnouncementText;
    std::shared_ptr<Util::SFX> m_GameOverSFX;
    std::shared_ptr<Util::SFX> m_GameWinningSFX;
    bool m_gameHasWon = false;

    int m_score = 0;
    int m_lastLifeScoreMilestone = 0;
    std::shared_ptr<GameText> m_scoreText;
};

#endif
