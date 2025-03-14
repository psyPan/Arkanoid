#ifndef APP_HPP
#define APP_HPP

#include "Ball.hpp"
#include "Character.hpp"
#include "LevelManager.hpp"
#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"
#include "Entity.hpp"
#include "Util/Time.hpp"

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
};

#endif
