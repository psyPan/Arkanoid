#include "App.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Brick.hpp"
#include "GameText.hpp"
#include "Util/Animation.hpp"
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

        if (m_LevelManager->GetBricks().empty() || AllBrickIsGold()){
            m_level++;
            Restart(false);
            InitGame(false);
        }

        if (m_score >= m_lastLifeScoreMilestone + 10000) {
            m_lives++;  // Only adds 1 life
            m_lastLifeScoreMilestone += 10000;
        }

        for (auto i = 0; i < m_Balls.size(); i++){
            // m_ball is sticky or not
            if (m_Balls[i]->IsSticky()){
                if (!m_ball_Stucked){
                    m_Balls[i]->SetPosition({m_Vaus->GetPosition().x + 5, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Balls[i]->GetScaledSize().y/2});
                }
                else{
                    m_Balls[i]->SetPosition({m_Balls[i]->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Balls[i]->GetScaledSize().y/2});
                }
            }

            if (!m_Balls[i]->IsSticky()){
                m_Vaus->SetStartingState(false);
                m_Balls[i]->SetPosition({m_Balls[i]->GetPosition().x + (m_Balls[i]->GetVelocity().x * m_Time.GetDeltaTime()), m_Balls[i]->GetPosition().y + (m_Balls[i]->GetVelocity().y * m_Time.GetDeltaTime())});
                // "speed * GetDeltaTime" to have uniform speed on PCs with different FPS.
            }

            // Bouncing against the border
            // Right border
            if (m_Balls[i]->GetPosition().x + m_Balls[i]->GetScaledSize().x / 2 > (m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24)){
                m_Balls[i]->SetPosition({m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24 - m_Balls[i]->GetScaledSize().x / 2, m_Balls[i]->GetPosition().y});
                m_Balls[i]->SetVelocity(glm::vec2{-m_Balls[i]->GetVelocity().x, m_Balls[i]->GetVelocity().y});
            }
            // Upper border
            if (m_Balls[i]->GetPosition().y + m_Balls[i]->GetScaledSize().y / 2 > (m_LevelManager->GetBackgroundImage()->GetScaledSize().y / 2 - 24)){
                m_Balls[i]->SetPosition({m_Balls[i]->GetPosition().x, m_LevelManager->GetBackgroundImage()->GetScaledSize().y / 2 - 24 - m_Balls[i]->GetScaledSize().y / 2});
                m_Balls[i]->SetVelocity(glm::vec2{m_Balls[i]->GetVelocity().x, -m_Balls[i]->GetVelocity().y});
                if (m_level != 9){
                    m_Balls[i]->MaximizeSpeed();
                }
            }
            // Left border
            if (m_Balls[i]->GetPosition().x - m_Balls[i]->GetScaledSize().x / 2 < -(m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 - 24)){
                m_Balls[i]->SetPosition({ -m_LevelManager->GetBackgroundImage()->GetScaledSize().x / 2 + 24 + m_Balls[i]->GetScaledSize().x / 2, m_Balls[i]->GetPosition().y});
                m_Balls[i]->SetVelocity(glm::vec2{-m_Balls[i]->GetVelocity().x, m_Balls[i]->GetVelocity().y});
            }

            // Collision between m_Vaus and m_Balls[i]
            if ((m_Vaus->GetAABB().Intersects(m_Balls[i]->GetAABB())) && (!m_ball_Stucked)) {
                m_Vaus->HandleCollisionWithBall(m_Balls[i]);
            }
        }

        if (isSpawningPill){
            m_Pill->SetPosition({m_Pill->GetPosition().x + 0, m_Pill->GetPosition().y + (m_Pill->GetVelocity().y * m_Time.GetDeltaTime())});
            // Collision between m_Vaus and m_Pill
            if (m_Pill->GetAABB().Intersects(m_Vaus->GetAABB())){
                m_Vaus->HandleCollisionWithPill(m_Pill);
                pendingPillType = m_Vaus->GetCurrentPill();
                if (pendingPillType == Pill::PILL_TYPE::PINK){
                    m_score += 10000;
                }
                else{
                    m_score += 1000;
                }

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

        DeleteInactiveBall();

        CheckForCollision();

        WhenPlayerLosesBall();

        DetectGameOver();

        VausHoldBall();

        UpdateScoreText();

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
    for (auto i = 0; i < m_Balls.size(); i++){
        m_Balls[i]->SetIsSticky(false);
    }
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
            for (auto i = 0; i < m_Balls.size(); i++){
                m_Balls[i]->SetIsSticky(false);
            }
            m_lives++;
            break;
        case Pill::PILL_TYPE::PINK:
            m_has_Glue = false;
            m_ball_Stucked = false;
            for (auto i = 0; i < m_Balls.size(); i++){
                m_Balls[i]->SetIsSticky(false);
            }
            m_level++;
            Restart(false);
            InitGame(false);
            break;
        case Pill::PILL_TYPE::LIGHTBLUE:
            m_has_Glue = false;
            m_ball_Stucked = false;
            for (auto i = 0; i < m_Balls.size(); i++){
                m_Balls[i]->SetIsSticky(false);
            }
            ActivateDisruption();
            break;
        case Pill::PILL_TYPE::ORANGE:
            m_has_Glue = false;
            m_ball_Stucked = false;
            for (auto i = 0; i < m_Balls.size(); i++){
                m_Balls[i]->SetIsSticky(false);
                m_Balls[i]->SlowDownSpeed();
            }
            break;
    }
}

void App::VausHoldBall(){
    if (m_has_Glue){
        m_Vaus->SetImage(RESOURCE_DIR"/Image/Vaus/Normal0.png");
        for (auto i = 0; i < m_Balls.size(); i++){
            if (m_Vaus->GetAABB().Intersects(m_Balls[i]->GetAABB())){
                m_Balls[i]->SetPosition(glm::vec2{m_Balls[i]->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Balls[i]->GetScaledSize().y/2});
                m_ball_Stucked = true;
                m_Balls[i]->SetIsSticky(true);
                m_Balls[i]->SetStickingPosX(abs(m_Balls[i]->GetPosition().x - m_Vaus->GetPosition().x));

            }
        }
    }
}

void App::ActivateDisruption(){
    if (m_Balls.empty()){
        std::cout << "There is no ball." << std::endl;
        return;
    }

    m_Vaus->SetImage(RESOURCE_DIR"/Image/Vaus/Normal0.png");
    // Assuming m_Ball is the current active ball
    glm::vec2 currentPos = m_Balls[0]->GetPosition();
    glm::vec2 currentVel = m_Balls[0]->GetVelocity();

    // Define angles for the new balls
    float angleOffset = 15.0f; // degrees
    float speed = glm::length(currentVel);

    // Calculate new velocities
    glm::vec2 velLeft = RotateVector(currentVel, -angleOffset);
    glm::vec2 velRight = RotateVector(currentVel, angleOffset);

    // Create new balls
    auto ballLeft = std::make_shared<Ball>(RESOURCE_DIR"/Image/Ball/ball.png", false, glm::vec2{200,400});
    ballLeft->SetVelocity(glm::normalize(velLeft) * speed);
    ballLeft->SetPosition(currentPos);
    ballLeft->SetVisible(true);
    m_Root.AddChild(ballLeft);

    auto ballRight = std::make_shared<Ball>(RESOURCE_DIR"/Image/Ball/ball.png", false, glm::vec2{200,400});
    ballRight->SetVelocity(glm::normalize(velRight) * speed);
    ballRight->SetPosition(currentPos);
    ballRight->SetVisible(true);
    m_Root.AddChild(ballRight);

    // Add new balls to the game
    m_Balls.push_back(ballLeft);
    m_Balls.push_back(ballRight);
    m_active_ball_count += 2;
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

void App::DeleteInactiveBall(){
    for (auto it = m_Balls.begin(); it != m_Balls.end();){
        if ((*it)->IsOutOfBound(m_LevelManager)){
            (*it)->SetVisible(false);
            m_Root.RemoveChild(*it);
            it = m_Balls.erase(it);
            m_active_ball_count--;
        }
        else{
            ++it;
        }
    }
}

void App::CheckForCollision(){
    for (auto i = 0; i < m_Balls.size(); i++){
        // Find the primary brick that the ball has collided with
        std::shared_ptr<Brick> collidedBrick = m_LevelManager->PrimaryCollidedBrick(m_Balls[i]);
        if (collidedBrick) { // If there is a valid collided brick
            collidedBrick->HandleCollisionWithBall(m_Balls[i]);
            collidedBrick->OnHit();
            if (collidedBrick->IsDestroyed()){
                m_score += collidedBrick->GetPoint();
            }
            if (!isSpawningPill && collidedBrick->GetBrickType()!= Brick::BRICK_TYPE::SILVER && collidedBrick->GetBrickType()!= Brick::BRICK_TYPE::GOLD){
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
    }

    // Checking collision between Brick and Lasers.
    for (auto& laser: m_Vaus->GetLasers()){
        for (auto& brick : m_LevelManager->GetBricks()) {
            if (laser->GetAABB().Intersects(brick->GetAABB())) {
                brick->OnHit(); // damage logic
                m_score += brick->GetPoint();
                if (!isSpawningPill && brick->GetBrickType()!= Brick::BRICK_TYPE::SILVER && brick->GetBrickType()!= Brick::BRICK_TYPE::GOLD){
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
                for (auto i = 0; i < m_Balls.size(); i++){
                    if (m_Balls[i]->GetPosition().x > m_Vaus->GetPosition().x){
                        m_Balls[i]->SetPosition(glm::vec2{m_Vaus->GetPosition().x + m_Balls[i]->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Balls[i]->GetScaledSize().y/2});
                    }
                    else{
                        m_Balls[i]->SetPosition(glm::vec2{m_Vaus->GetPosition().x - m_Balls[i]->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Balls[i]->GetScaledSize().y/2});

                    }
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
                for (auto i = 0; i < m_Balls.size(); i++){
                    if (m_Balls[i]->GetPosition().x > m_Vaus->GetPosition().x){
                        m_Balls[i]->SetPosition(glm::vec2{m_Vaus->GetPosition().x + m_Balls[i]->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Balls[i]->GetScaledSize().y/2});
                    }
                    else{
                        m_Balls[i]->SetPosition(glm::vec2{m_Vaus->GetPosition().x - m_Balls[i]->GetStickingPosX(), m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Balls[i]->GetScaledSize().y/2});

                    }
                }
            }
        }
        for (auto i = 0; i < m_Balls.size(); i++){
            if (m_Balls[i]->IsSticky() && Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
                m_Vaus->GetVausBallSound()->Play();
                m_Balls[i]->SetIsSticky(false);
                m_Vaus->SetStartingState(false);
            }
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
                for (auto i = 0; i < m_Balls.size(); i++){
                    m_Balls[i]->SetIsSticky(false);
                }
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
    if (m_active_ball_count == 0) {
        m_lives--;
        m_Balls.clear();
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

    auto m_Ball = std::make_shared<Ball>(RESOURCE_DIR"/Image/Ball/ball.png", true, glm::vec2{200,400});
    m_Ball->SetZIndex(50);
    m_Ball->SetVisible(true);
    m_Ball->SetIsSticky(true);
    m_Ball->SetPosition({m_Vaus->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
    m_Root.AddChild(m_Ball);
    m_Balls.push_back(m_Ball);
    m_active_ball_count = 1;

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
    for (auto& ball: m_Balls){
        m_Root.RemoveChild(ball);
    }
    m_LevelManager->GetBricks().clear();
    m_Balls.clear();
    // Restarting m_LevelManager
    m_Root.RemoveChild(m_LevelManager->GetChild());
    m_LevelManager->GetChild().reset();
    m_LevelManager.reset();

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

    m_Root.RemoveChild(m_scoreText);
    m_scoreText->SetVisible(false);
    m_scoreText.reset();

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
        m_level = 15;
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

    // Score texts
    m_scoreText = std::make_shared<GameText>("Score: \n" + std::to_string(m_score), glm::vec2{-480,100}, 18);
    m_scoreText->SetVisible(true);
    m_scoreText->SetZIndex(50);
    m_Root.AddChild(m_scoreText);

    // Ball
    auto m_Ball = std::make_shared<Ball>(RESOURCE_DIR"/Image/Ball/ball.png", true, glm::vec2{200,400});
    m_Ball->SetZIndex(50);
    m_Ball->SetPosition({m_Vaus->GetPosition().x, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
    m_Ball->SetVisible(true);
    m_Balls.push_back(m_Ball);
    m_Root.AddChild(m_Ball);

    m_GameOverSFX = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sounds/GameOver.wav");

}

glm::vec2 App::RotateVector(const glm::vec2& vec, float angle){
    float radians = glm::radians(angle);
    float sinA = sin(radians);
    float cosA = cos(radians);
    return glm::vec2{
        vec.x * cosA - vec.y * sinA,
        vec.x * sinA + vec.y * cosA
    };
}

void App::UpdateScoreText(){
    m_scoreText->ChangeText("Score: \n" + std::to_string(m_score));
}

bool App::AllBrickIsGold(){
    int counter = 0;
    for (auto& brick: m_LevelManager->GetBricks()){
        if (brick->GetBrickType() == Brick::BRICK_TYPE::GOLD){
            counter++;
        }
    }
    return counter == m_LevelManager->GetBricks().size();
}


void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

