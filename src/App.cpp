#include "App.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Brick.hpp"
#include "GameText.hpp"
#include "Util/SFX.hpp"

void App::Start() {
    InitGame(true); // reset is true to make the game starting from level 1, lives with 3.
}

void App::Update() {
    m_Root.Update();
    HandleInput();
    if (m_gameIsRunning){
        //TODO: do your things here and delete this line <3
        UpdateLivesUI();

        if (m_LevelManager->GetBricks().empty()){
            m_level++;
            Restart(false);
            InitGame(false);
        }


        // m_ball is sticky or not
        if (m_Ball->IsSticky()){
            if (!m_ball_Stucked){
                m_Ball->SetPosition({m_Vaus->GetPosition().x + 5, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
            }
            else{
                m_Ball->SetPosition({m_Ball->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
            }
        }

        if (!m_Ball->IsSticky()){
            m_Vaus->SetStartingState(false);
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
            m_Ball->MaximizeSpeed();
        }
        // Left border
        if (m_Ball->GetPosition().x - m_Ball->GetScaledSize().x / 2 < -(m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24)){
            m_Ball->SetPosition({ -m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 + 24 + m_Ball->GetScaledSize().x / 2, m_Ball->GetPosition().y});
            m_Ball->SetVelocity(glm::vec2{-m_Ball->GetVelocity().x, m_Ball->GetVelocity().y});
        }

        // Collision between m_Vaus and m_Ball
        if ((m_Vaus->GetAABB().Intersects(m_Ball->GetAABB())) && (!m_ball_Stucked)) {
            m_Vaus->HandleCollisionWithBall(m_Ball);
        }

        if (isSpawningPill){
            m_Pill->SetPosition({m_Pill->GetPosition().x + 0, m_Pill->GetPosition().y + (m_Pill->GetVelocity().y * m_Time.GetDeltaTime())});
            // Collision between m_Vaus and m_Pill
            if (m_Pill->GetAABB().Intersects(m_Vaus->GetAABB())){
                m_Vaus->HandleCollisionWithPill(m_Pill);
                pendingPillType = m_Vaus->GetCurrentPill();
                if (pendingPillType == Pill::PILL_TYPE::BLUE || pendingPillType == Pill::PILL_TYPE::RED){
                    shouldReplaceVaus = true;
                }
                else{
                    otherPowerUp = true;
                }
                isSpawningPill = false;
                m_Pill->SetVisible(false);
                m_Root.RemoveChild(m_Pill);
                m_Pill.reset();
            }

            // when the pill moves out of screen
            else if (-(m_Pill->GetPosition().y - m_Pill->GetScaledSize().y / 2) >= m_LevelManager->GetBackgroundImage()->GetScaledSize().y / 2){
                isSpawningPill = false;
                m_Pill->SetVisible(false);
                m_Root.RemoveChild(m_Pill);
                m_Pill.reset();
            }
        }

        if (shouldReplaceVaus) {
            VausPowerUp();
            shouldReplaceVaus = false;
        }

        if (otherPowerUp){
            OtherPowerUp();
            otherPowerUp = false;
        }

        // Update the lasers' positions.
        for (auto& laser: m_Vaus->GetLasers()){
            laser->Update(m_LevelManager->GetBackgroundImage()->GetScaledSize());
        }

        // Delete the out of bound lasers.
        DeleteInactiveLasers();

        CheckForCollision();

        WhenPlayerLosesBall();

        DetectGameOver();

        VausHoldBall();

    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }

}

void App::CreatePill(const Pill::PILL_TYPE& pill, const glm::vec2& pos){
    switch (pill){
        case Pill::PILL_TYPE::BLUE:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/BluePill0.png",Pill::PILL_TYPE::BLUE, pos);
            m_Pill->SetVisible(true);
            m_Pill->SetZIndex(100);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::GREEN:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/GreenPill0.png",Pill::PILL_TYPE::GREEN, pos);
            m_Pill->SetVisible(true);
            m_Pill->SetZIndex(100);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::RED:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/RedPill0.png",Pill::PILL_TYPE::RED, pos);
            m_Pill->SetVisible(true);
            m_Pill->SetZIndex(100);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::GREY:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/GreyPill0.png",Pill::PILL_TYPE::GREY, pos);
            m_Pill->SetVisible(true);
            m_Pill->SetZIndex(100);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::PINK:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/PinkPill0.png",Pill::PILL_TYPE::PINK, pos);
            m_Pill->SetVisible(true);
            m_Pill->SetZIndex(100);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::LIGHTBLUE:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/LightBluePill0.png",Pill::PILL_TYPE::LIGHTBLUE, pos);
            m_Pill->SetVisible(true);
            isSpawningPill = true;
            m_Pill->SetZIndex(100);
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::ORANGE:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/OrangePill0.png",Pill::PILL_TYPE::ORANGE, pos);
            m_Pill->SetVisible(true);
            m_Pill->SetZIndex(100);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
    }
}

void App::VausPowerUp(){
    m_has_Glue = false;
    m_Ball->SetIsSticky(false);
    m_ball_Stucked = false;
    glm::vec2 currentPos = m_Vaus->GetPosition();
    for (auto& laser: m_Vaus->GetLasers()){
        m_Root.RemoveChild(laser);
    }
    m_Vaus->ClearLasers();
    m_Root.RemoveChild(m_Vaus);
    m_Vaus.reset();
    switch (pendingPillType){
        case Pill::PILL_TYPE::BLUE:
            m_Vaus = std::make_shared<Character>(RESOURCE_DIR"/Image/Vaus/Long0.png");
            break;
        case Pill::PILL_TYPE::RED:
            m_Vaus = std::make_shared<Character>(RESOURCE_DIR"/Image/Vaus/Shoot0.png");
            break;
    }
    m_Vaus->SetZIndex(50);
    m_Vaus->SetPosition(currentPos);
    m_Vaus->SetVisible(true);
    m_Root.AddChild(m_Vaus);
}

void App::OtherPowerUp(){
    switch (pendingPillType){
        case Pill::PILL_TYPE::GREEN:
            m_has_Glue = true;
            break;
        case Pill::PILL_TYPE::GREY:
            m_has_Glue = false;
            m_ball_Stucked = false;
            m_Ball->SetIsSticky(false);
            m_lives++;
            break;
        case Pill::PILL_TYPE::PINK:
            m_has_Glue = false;
            m_ball_Stucked = false;
            m_Ball->SetIsSticky(false);
            m_level++;
            Restart(false);
            InitGame(false);
            break;
        case Pill::PILL_TYPE::LIGHTBLUE:
            m_has_Glue = false;
            m_ball_Stucked = false;
            m_Ball->SetIsSticky(false);
            std::cout << "LIGHTBLUE" << std::endl;
            break;
        case Pill::PILL_TYPE::ORANGE:
            m_has_Glue = false;
            m_ball_Stucked = false;
            m_Ball->SetIsSticky(false);
            m_Ball->SlowDownSpeed();
            break;
    }
}

void App::VausHoldBall(){
    if (m_has_Glue){
        m_Vaus->SetImage(RESOURCE_DIR"/Image/Vaus/Normal0.png");
        if (m_Vaus->GetAABB().Intersects(m_Ball->GetAABB())){
            m_Ball->SetPosition(glm::vec2{m_Ball->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
            m_ball_Stucked = true;
            m_Ball->SetIsSticky(true);
            m_Ball->SetStickingPosX(abs(m_Ball->GetPosition().x - m_Vaus->GetPosition().x));

        }
    }
}

void App::DeleteInactiveLasers(){
    auto& lasers = m_Vaus->GetLasers();
    for (auto it = lasers.begin(); it != lasers.end();){
        if (!(*it)->IsActive()){
            (*it)->SetVisible(false);
            m_Root.RemoveChild(*it);
            it = lasers.erase(it);
        }
        else{
            ++it;
        }
    }
}

void App::CheckForCollision(){
    // Find the primary brick that the ball has collided with
    std::shared_ptr<Brick> collidedBrick = m_LevelManager->PrimaryCollidedBrick(m_Ball);
    if (collidedBrick) { // If there is a valid collided brick
        collidedBrick->HandleCollisionWithBall(m_Ball);
        collidedBrick->OnHit();
        if (!isSpawningPill && collidedBrick->GetBrickType()!= Brick::BRICK_TYPE::SILVER){
            Pill::PILL_TYPE spawningPill = collidedBrick->SpawnPill();
            CreatePill(spawningPill, collidedBrick->GetPosition());
        }
        if (collidedBrick->IsDestroyed()) {
            collidedBrick->SetVisible(false);

            // Remove the brick from the scene and level
            m_Root.RemoveChild(std::dynamic_pointer_cast<Util::GameObject>(collidedBrick));

            // Find and erase the brick from the list
            auto& bricks = m_LevelManager->GetBricks();
            auto it = std::find(bricks.begin(), bricks.end(), collidedBrick); // it will be the primary collided brick.
            if (it != bricks.end()) {
                bricks.erase(it);
            }
        }
    }

    // Checking collision between Brick and Lasers.
    for (auto& laser: m_Vaus->GetLasers()){
        for (auto& brick : m_LevelManager->GetBricks()) {
            if (laser->GetAABB().Intersects(brick->GetAABB())) {
                brick->OnHit(); // damage logic
                if (!isSpawningPill && brick->GetBrickType()!= Brick::BRICK_TYPE::SILVER){
                    Pill::PILL_TYPE spawningPill = brick->SpawnPill();
                    CreatePill(spawningPill, brick->GetPosition());
                }

                if (brick->IsDestroyed()) {
                    brick->SetVisible(false);
                    bricksToRemove.push_back(brick);
                    m_Root.RemoveChild(std::dynamic_pointer_cast<Util::GameObject>(brick));
                }

                laser->SetActive(false); // deactivate laser
                break; // one laser hits only one brick
            }
        }
    }
    // Remove destroyed bricks from LevelManager list
    auto& bricks = m_LevelManager->GetBricks();
    for (auto& brick : bricksToRemove) {
        auto it = std::find(bricks.begin(), bricks.end(), brick);
        if (it != bricks.end()) {
            bricks.erase(it);
        }
    }
}

void App::UpdateLivesUI(){
    if (m_lives != m_old_lives){
        m_num_of_lives_Text->ChangeText(" x " + std::to_string(m_lives));
        m_old_lives = m_lives;
    }
}

void App::HandleInput(){

    if ((!m_ballOutOfBound) && (Util::Input::IsKeyUp(Util::Keycode::P))){
        m_gameIsRunning = !m_gameIsRunning;
    }
    if (!m_gameIsRunning){
        if (!m_ballOutOfBound){
            m_AnnouncementText->ChangeText("Game is paused.\nPress (P) to play.");
        }
    }
    else{
        m_AnnouncementText->ChangeText("Game is running.\nPress (P) to pause.");
    }
    if (m_gameIsRunning){
        // Movement of Vaus
        if (Util::Input::IsKeyPressed(Util::Keycode::A)){
            m_Vaus->SetPosition({m_Vaus->GetPosition().x - 10, m_Vaus->GetPosition().y});
            float leftBorder = -((m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24) - m_Vaus->GetScaledSize().x / 2);
            // 24 is the white border bar width
            if (m_Vaus->GetPosition().x < leftBorder){
                m_Vaus->SetPosition({leftBorder, m_Vaus->GetPosition().y});
            }
            if (m_ball_Stucked){
                if (m_Ball->GetPosition().x > m_Vaus->GetPosition().x){
                    m_Ball->SetPosition(glm::vec2{m_Vaus->GetPosition().x + m_Ball->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
                }
                else{
                    m_Ball->SetPosition(glm::vec2{m_Vaus->GetPosition().x - m_Ball->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});

                }
            }
        }
        else if (Util::Input::IsKeyPressed(Util::Keycode::D)){
            m_Vaus->SetPosition({m_Vaus->GetPosition().x + 10, m_Vaus->GetPosition().y});
            float rightBorder = ((m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24) - m_Vaus->GetScaledSize().x / 2);
            if (m_Vaus->GetPosition().x > rightBorder){
                m_Vaus->SetPosition({rightBorder, m_Vaus->GetPosition().y});
            }
            if (m_ball_Stucked){
                if (m_Ball->GetPosition().x > m_Vaus->GetPosition().x){
                    m_Ball->SetPosition(glm::vec2{m_Vaus->GetPosition().x + m_Ball->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
                }
                else{
                    m_Ball->SetPosition(glm::vec2{m_Vaus->GetPosition().x - m_Ball->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});

                }
            }
        }
        if (m_Ball->IsSticky() && Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
            m_Vaus->GetVausBallSound()->Play();
            m_Ball->SetIsSticky(false);
            m_Vaus->SetStartingState(false);
        }
        // Laser shooting Vaus.
        if (m_Vaus->GetImagePath() == RESOURCE_DIR"/Image/Vaus/Shoot0.png"){
            // Vaus shooting laser
            if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
                m_Vaus->FireLaser(m_Time.GetElapsedTimeMs(), m_Root);
            }
        }

        if (m_has_Glue){
            if ((m_ball_Stucked) && (Util::Input::IsKeyPressed(Util::Keycode::SPACE))){
                m_Vaus->GetVausBallSound()->Play();
                m_ball_Stucked = false;
                m_Ball->SetIsSticky(false);
            }
        }

    }
    if (m_ballOutOfBound){
        if (Util::Input::IsKeyUp(Util::Keycode::R)){
            ResumePlayerLosesBall();
        }
    }

    if (m_gameOver){
        m_gameIsRunning = false;
        m_AnnouncementText->ChangeText("Game Over\nPress (R) to restart");
        if (Util::Input::IsKeyUp(Util::Keycode::R)){
            Restart(true);
            InitGame(true);
        }
    }

}

void App::WhenPlayerLosesBall(){
    if ((-(m_Ball->GetPosition().y - m_Ball->GetScaledSize().y / 2) >= m_LevelManager->GetBackgroundImage()->GetScaledSize().y / 2 + 50) && (m_active_ball_count == 1)) {
        m_lives--;
        m_ballOutOfBound = true;
        m_AnnouncementText->ChangeText("You lost the ball.\nOne live is deducted.\nCurrent lives = " + std::to_string(m_lives)+ "\nPress (R) to resume.");
        m_AnnouncementText->SetPosition(glm::vec2{480,200});
        m_gameIsRunning = false;
    }
}

void App::ResumePlayerLosesBall(){
    m_AnnouncementText->ChangeText("Game is running.\n Press (P) to pause.");
    m_gameIsRunning = true;
    m_ballOutOfBound = false;
    m_has_Glue = false;
    m_Vaus->SetStartingState(true);
    m_Vaus->SetImage(RESOURCE_DIR"/Image/Vaus/Normal0.png");

    m_Ball->SetVelocity(glm::vec2{200,400});
    m_Ball->SetIsSticky(true);
    m_Ball->SetPosition({m_Vaus->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
    if (isSpawningPill){
        isSpawningPill = false;
        m_Pill->SetVisible(false);
        m_Root.RemoveChild(m_Pill);
        m_Pill.reset();
    }
    if (!m_Vaus->GetLasers().empty()){
        for (auto& laser: m_Vaus->GetLasers()){
            m_Root.RemoveChild(laser);
        }
        m_Vaus->ClearLasers();
    }
}

void App::DetectGameOver(){
    if (m_lives == 0){
        m_GameOverSFX->Play();
        m_gameOver = true;
    }
}

void App::Restart(bool reset){ // reset is true when the game is resetting from the start(Level 1)
    // Remove Bricks
    for (auto& brick : m_LevelManager->GetBricks()) {
        m_Root.RemoveChild(brick);
    }
    m_LevelManager->GetBricks().clear();
    // Restarting m_LevelManager
    m_Root.RemoveChild(m_LevelManager->GetChild());
    m_LevelManager->GetChild().reset();
    m_LevelManager.reset();

    m_Root.RemoveChild(m_Ball);
    m_Ball->SetVisible(false);
    m_Ball.reset();

    // Emptying lasers
    for (auto& laser: m_Vaus->GetLasers()){
        m_Root.RemoveChild(laser);
    }
    m_Vaus->ClearLasers();

    m_Root.RemoveChild(m_Vaus);
    m_Vaus->SetVisible(false);
    m_Vaus.reset();

    m_Root.RemoveChild(m_AnnouncementText);
    m_AnnouncementText->SetVisible(false);
    m_AnnouncementText.reset();

    if (reset){

        m_Root.RemoveChild(m_Icon);
        m_Icon->SetVisible(false);
        m_Icon.reset();

        m_Root.RemoveChild(m_num_of_lives_Text);
        m_num_of_lives_Text->SetVisible(false);
        m_num_of_lives_Text.reset();
    }
    if (isSpawningPill){
        isSpawningPill = false;
        m_Pill->SetVisible(false);
        m_Root.RemoveChild(m_Pill);
        m_Pill.reset();
    }
}

void App::InitGame(bool reset){
    if (reset){
        LOG_TRACE("Start");
        m_lives = 3;
        m_level = 0;
        m_gameIsRunning = true;
        m_gameOver = false;
        m_CurrentState = State::UPDATE;
        m_ballOutOfBound = false;
        m_has_Glue = false;
        m_ball_Stucked = false;
        m_active_ball_count = 1;
    }
    m_LevelManager = std::make_shared<LevelManager>(m_level);
    m_Root.AddChild(m_LevelManager->GetChild());
    m_LevelManager->CreateBrick(m_Root);

    if (reset){
        // Player lives icon and UI
        m_Icon = std::make_shared<Entity>(RESOURCE_DIR"/Image/Vaus/small.png");
        glm::vec2 icon_pos = glm::vec2{-(m_LevelManager->GetBackgroundImage()->GetScaledSize().x/2) + m_Icon->GetScaledSize().x, -(m_LevelManager->GetBackgroundImage()->GetScaledSize().y/2) + m_Icon->GetScaledSize().y};
        m_Icon->SetPosition(icon_pos);
        m_Icon->SetVisible(true);
        m_Icon->SetZIndex(50);
        m_Root.AddChild(m_Icon);
        glm::vec2 text_pos = glm::vec2{icon_pos.x + m_Icon->GetScaledSize().x, icon_pos.y};
        m_num_of_lives_Text = std::make_shared<GameText>(" x " + std::to_string(m_lives), text_pos, 15);
        m_num_of_lives_Text->SetVisible(true);
        m_num_of_lives_Text->SetZIndex(50);
        m_Root.AddChild(m_num_of_lives_Text);
    }
    // Vaus
    m_Vaus = std::make_shared<Character>(RESOURCE_DIR"/Image/Vaus/Normal0.png");
    m_Vaus->SetZIndex(50);
    m_Vaus->SetPosition({0, -300});
    m_Vaus->SetVisible(true);
    m_Root.AddChild(m_Vaus);

    // Announcement texts
    m_AnnouncementText =  std::make_shared<GameText>("Game is running.\nPress (P) to pause.", glm::vec2{480,200}, 18);
    m_AnnouncementText->SetVisible(true);
    m_AnnouncementText->SetZIndex(50);
    m_Root.AddChild(m_AnnouncementText);

    // Ball
    m_Ball = std::make_shared<Ball>(RESOURCE_DIR"/Image/Ball/ball.png", true, glm::vec2{200,400});
    m_Ball->SetZIndex(50);
    m_Ball->SetPosition({m_Vaus->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
    m_Ball->SetVisible(true);
    m_Root.AddChild(m_Ball);

    m_GameOverSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/GameOver.wav");

}


void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

