#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
    m_LevelManager = std::make_shared<LevelManager>();
    m_Root.AddChild(m_LevelManager->GetChild());

    // Vaus
    m_Vaus = std::make_shared<Character>(RESOURCE_DIR"/Image/Vaus/Normal.png");
    m_Vaus->SetZIndex(50);
    m_Vaus->SetPosition({0, -300});
    m_Vaus->SetVisible(true);
    m_Root.AddChild(m_Vaus);

    // Ball
    m_Ball = std::make_shared<Ball>(RESOURCE_DIR"/Image/Ball/ball.png", true, glm::vec2{100,300});
    m_Ball->SetZIndex(50);
    m_Ball->SetPosition({m_Vaus->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
    m_Ball->SetVisible(true);
    m_Root.AddChild(m_Ball);

    // Bricks
    m_LevelManager->CreateBrick(m_Root);

}

void App::Update() {
    m_Root.Update();
    
    //TODO: do your things here and delete this line <3

    // Movement of Vaus
    if (Util::Input::IsKeyPressed(Util::Keycode::A)){
        m_Vaus->SetPosition({m_Vaus->GetPosition().x - 10, m_Vaus->GetPosition().y});
        float leftBorder = -((m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24) - m_Vaus->GetScaledSize().x / 2);
        // 24 is the white border bar width
        if (m_Vaus->GetPosition().x < leftBorder){
            m_Vaus->SetPosition({leftBorder, m_Vaus->GetPosition().y});
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::D)){
        m_Vaus->SetPosition({m_Vaus->GetPosition().x + 10, m_Vaus->GetPosition().y});
        float rightBorder = ((m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24) - m_Vaus->GetScaledSize().x / 2);
        if (m_Vaus->GetPosition().x > rightBorder){
            m_Vaus->SetPosition({rightBorder, m_Vaus->GetPosition().y});
        }
    }

    // m_ball is sticky or not
    if (m_Ball->IsSticky()){
        m_Ball->SetPosition({m_Vaus->GetPosition().x + 5, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});

        if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
            m_Ball->SetIsSticky(false);

        }
    }

    if (!m_Ball->IsSticky()){
        m_Ball->SetPosition({m_Ball->GetPosition().x + (m_Ball->GetVelocity().x * m_Time.GetDeltaTime()), m_Ball->GetPosition().y + (m_Ball->GetVelocity().y * m_Time.GetDeltaTime())});
        // "speed * GetDeltaTime" to have uniform speed on PCs with different FPS.
    }

    // Bouncing against the border
    // Right border
    if (m_Ball->GetPosition().x + m_Ball->GetScaledSize().x / 2 > (m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24)){
        m_Ball->SetPosition({m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24 - m_Ball->GetScaledSize().x / 2, m_Ball->GetPosition().y});
        m_Ball->SetVelocity(glm::vec2{-m_Ball->GetVelocity().x, m_Ball->GetVelocity().y});
    }
    // Upper border
    if (m_Ball->GetPosition().y + m_Ball->GetScaledSize().y / 2 > (m_LevelManager->GetBackgroundImage()->GetScaledSize().y / 2 - 24)){
        m_Ball->SetPosition({m_Ball->GetPosition().x, m_LevelManager->GetBackgroundImage()->GetScaledSize().y / 2 - 24 - m_Ball->GetScaledSize().y / 2});
        m_Ball->SetVelocity(glm::vec2{m_Ball->GetVelocity().x, -m_Ball->GetVelocity().y});
    }
    // Left border
    if (m_Ball->GetPosition().x - m_Ball->GetScaledSize().x / 2 < -(m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24)){
        m_Ball->SetPosition({ -m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 + 24 + m_Ball->GetScaledSize().x / 2, m_Ball->GetPosition().y});
        m_Ball->SetVelocity(glm::vec2{-m_Ball->GetVelocity().x, m_Ball->GetVelocity().y});
    }

    // Collision between m_Vaus and m_Ball
    if (m_Vaus->CollideWithBall(m_Ball)) {
        m_Vaus->HandleCollisionWithBall(m_Ball);
    }

    // Collision between each brick and m_Ball
    auto& bricks = m_LevelManager->GetBricks();
    for (auto it = bricks.begin(); it != bricks.end(); ) {
        if ((*it)->CollideWithBall(m_Ball)) {
            (*it)->HandleCollisionWithBall(m_Ball);
            (*it)->DecreseHitCount();

            if ((*it)->GetHitCount() == 0) {
                (*it)->SetVisible(false);
                m_Root.RemoveChild(*it); // Ensure this does not invalidate `it`
                it = bricks.erase(it);   // Get valid iterator after erasing
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
