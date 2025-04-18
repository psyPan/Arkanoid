#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Brick.hpp"
void LogBrickType(Brick::BRICK_TYPE brickType) {
    switch (brickType) {
        case Brick::BRICK_TYPE::NULL_BRICK: std::cout << "Brick Type: NULL_BRICK: "; break;
        case Brick::BRICK_TYPE::GOLD: std::cout << "Brick Type: GOLD: "; break;
        case Brick::BRICK_TYPE::SILVER: std::cout << "Brick Type: SILVER: "; break;
        case Brick::BRICK_TYPE::WHITE: std::cout << "Brick Type: WHITE: "; break;
        case Brick::BRICK_TYPE::RED: std::cout << "Brick Type: RED: "; break;
        case Brick::BRICK_TYPE::GREEN: std::cout << "Brick Type: GREEN: "; break;
        case Brick::BRICK_TYPE::BLUE: std::cout << "Brick Type: BLUE: "; break;
        case Brick::BRICK_TYPE::YELLOW: std::cout << "Brick Type: YELLOW: "; break;
        case Brick::BRICK_TYPE::LIGHT_BLUE: std::cout << "Brick Type: LIGHT_BLUE: "; break;
        case Brick::BRICK_TYPE::PINK: std::cout << "Brick Type: PINK: "; break;
        case Brick::BRICK_TYPE::ORANGE: std::cout << "Brick Type: ORANGE: "; break;
        default: std::cout << "Brick Type: UNKNOWN: "; break;
    }
}


void App::Start() {
    LOG_TRACE("Start");
    m_level = 1;
    m_CurrentState = State::UPDATE;
    m_LevelManager = std::make_shared<LevelManager>(m_level);
    m_Root.AddChild(m_LevelManager->GetChild());

    // Vaus
    m_Vaus = std::make_shared<Character>(RESOURCE_DIR"/Image/Vaus/Normal0.png");
    m_Vaus->SetZIndex(50);
    m_Vaus->SetPosition({0, -300});
    m_Vaus->SetVisible(true);
    m_Root.AddChild(m_Vaus);

    // Ball
    m_Ball = std::make_shared<Ball>(RESOURCE_DIR"/Image/Ball/ball.png", true, glm::vec2{60,60});
    std::cout << "In App Start" << std::endl;
    std::cout << "Ball speed: x = " << m_Ball->GetVelocity().x << std::endl;
    std::cout << "Ball speed: y = " << m_Ball->GetVelocity().y << std::endl;
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

    if (m_LevelManager->GetBricks().empty()){
        m_Root.RemoveChild(m_LevelManager->GetChild());
        m_LevelManager->GetChild().reset();
        m_LevelManager.reset();
        m_LevelManager = std::make_shared<LevelManager>(++m_level);
        m_Root.AddChild(m_LevelManager->GetChild()); // add new background
        m_LevelManager->CreateBrick(m_Root);
    }

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
    glm::vec2 startingVelocity = m_Ball->GetVelocity();
    if (m_Ball->IsSticky()){
        m_Ball->SetPosition({m_Vaus->GetPosition().x + 5, m_Vaus->GetPosition().y + m_Vaus->GetScaledSize().y/2 + m_Ball->GetScaledSize().y/2});
        m_Ball->SetVelocity(startingVelocity);

        if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
            m_Ball->SetIsSticky(false);
            std::cout << "IN sticky" << std::endl;
            std::cout << "Ball speed: x = " << m_Ball->GetVelocity().x << std::endl;
            std::cout << "Ball speed: y = " << m_Ball->GetVelocity().y << std::endl;
        }
    }

    if (!m_Ball->IsSticky()){
        m_Ball->SetPosition({m_Ball->GetPosition().x + (m_Ball->GetVelocity().x * m_Time.GetDeltaTime()), m_Ball->GetPosition().y + (m_Ball->GetVelocity().y * m_Time.GetDeltaTime())});
        std::cout << "Ball speed: x = " << m_Ball->GetVelocity().x << std::endl;
        std::cout << "Ball speed: y = " << m_Ball->GetVelocity().y << std::endl;
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
    if (m_Vaus->GetAABB().Intersects(m_Ball->GetAABB())) {
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

    // Laser shooting Vaus.
    if (m_Vaus->GetImagePath() == RESOURCE_DIR"/Image/Vaus/Shoot0.png"){
        // Vaus shooting laser
        if (Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
            m_Vaus->FireLaser(m_Time.GetElapsedTimeMs(), m_Root);
        }
    }

    // Update the lasers' positions.
    for (auto& laser: m_Vaus->GetLasers()){
        laser->Update(m_LevelManager->GetBackgroundImage()->GetScaledSize());
    }

    // Delete the out of bound lasers.
    DeleteInactiveLasers();

    CheckForCollision();



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
            m_Pill->SetZIndex(50);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::GREEN:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/GreenPill0.png",Pill::PILL_TYPE::GREEN, pos);
        m_Pill->SetVisible(true);
        m_Pill->SetZIndex(50);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::RED:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/RedPill0.png",Pill::PILL_TYPE::RED, pos);
        m_Pill->SetVisible(true);
        m_Pill->SetZIndex(50);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::GREY:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/GreyPill0.png",Pill::PILL_TYPE::GREY, pos);
        m_Pill->SetVisible(true);
        m_Pill->SetZIndex(50);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::PINK:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/PinkPill0.png",Pill::PILL_TYPE::PINK, pos);
        m_Pill->SetVisible(true);
        m_Pill->SetZIndex(50);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::LIGHTBLUE:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/LightBluePill0.png",Pill::PILL_TYPE::LIGHTBLUE, pos);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
        case Pill::PILL_TYPE::ORANGE:
            m_Pill = std::make_shared<Pill>(RESOURCE_DIR"/Image/Pill/OrangePill0.png",Pill::PILL_TYPE::ORANGE, pos);
        m_Pill->SetVisible(true);
        m_Pill->SetZIndex(50);
            isSpawningPill = true;
            m_Root.AddChild(m_Pill);
            break;
    }
}

void App::VausPowerUp(){
    glm::vec2 currentPos = m_Vaus->GetPosition();
    m_Root.RemoveChild(m_Vaus);
    m_Vaus.reset();
    switch (pendingPillType){
        case Pill::PILL_TYPE::BLUE:
            // m_Root.RemoveChild(m_Vaus);
            // m_Vaus.reset();
            m_Vaus = std::make_shared<Character>(RESOURCE_DIR"/Image/Vaus/Long0.png");
            break;
        case Pill::PILL_TYPE::RED:
            // m_Root.RemoveChild(m_Vaus);
            // m_Vaus.reset();
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
            std::cout << "GREEN" << std::endl;
            break;
        case Pill::PILL_TYPE::GREY:
            std::cout << "GREY" << std::endl;
            break;
        case Pill::PILL_TYPE::PINK:
            std::cout << "PINK" << std::endl;
            break;
        case Pill::PILL_TYPE::LIGHTBLUE:
            std::cout << "LIGHTBLUE" << std::endl;
            break;
        case Pill::PILL_TYPE::ORANGE:
            std::cout << "ORANGE" << std::endl;
            break;
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

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

