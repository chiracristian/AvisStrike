#include "lab_m1/AvisStrike/AvisStrikeScene.h"

#include <vector>
#include <iostream>
#include <iomanip>

#include "lab_m1/AvisStrike/transform2D.h"
#include "lab_m1/AvisStrike/object2D.h"
#include "Constants.h"

#include "shapes/ShapeFactory.h"
#include "shapes/ArrowShape.h"
#include "shapes/ChickenShape.h"
#include "shapes/EngineShape.h"
#include "shapes/SolidBlockShape.h"
#include "shapes/StartButtonShape.h"
#include "shapes/TurretShape.h"

#include "SpaceshipData.h"

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

using namespace m1;

AvisStrikeScene::AvisStrikeScene()
    : placementGrid(SPACESHIP_GRID_ROWS, SPACESHIP_GRID_COLS)
{

}


AvisStrikeScene::~AvisStrikeScene()
{
    
}

template <typename T>
void deleteSwapAndPop(std::vector<T>& elements, size_t index)
{
    elements[index] = std::move(elements.back());
    elements.pop_back();
}

void AvisStrikeScene::initializeMeshes()
{
    // Game components

    // Chicken
    ChickenShape chickenShape;
    Mesh* chickenMesh = chickenShape.convertToMesh("chicken");
    AddMeshToList(chickenMesh);

    // Player projectile
    Shape projectileShape = ShapeFactory::circle(
        PROJECTILE_RADIUS,
        PROJECTILE_COLOR
    );
    Mesh* projectileMesh = projectileShape.convertToMesh("projectile");
    AddMeshToList(projectileMesh);

    // Egg
    Shape eggShape = ShapeFactory::ellipse(EGG_X_RADIUS, EGG_Y_RADIUS, EGG_COLOR);
    Mesh* eggMesh = eggShape.convertToMesh("egg");
    AddMeshToList(eggMesh);

    // Spaceship solid block
    Shape solidBlockShape = SolidBlockShape();
    Mesh* solidBlockMesh = solidBlockShape.convertToMesh("solid_block");
    AddMeshToList(solidBlockMesh);

    // Spaceship turret
    Shape turretShape = TurretShape();
    Mesh* turretMesh = turretShape.convertToMesh("turret");
    AddMeshToList(turretMesh);

    // Spaceship engine
    Shape engineShape = EngineShape();
    Mesh* engineMesh = engineShape.convertToMesh("engine");
    AddMeshToList(engineMesh);

    // Editor components
    // Component windows
    Shape componentWindowShape = ShapeFactory::rectangleOutline(
        COMPONENT_WINDOW_WIDTH,
        COMPONENT_WINDOW_HEIGHT,
        COMPONENT_WINDOW_OUTLINE_COLOR
    );
    Mesh* componentWindowMesh = componentWindowShape.convertToMesh(
        "component_window"
    );
    AddMeshToList(componentWindowMesh);

    // Spaceship grid
    Shape gridWindowShape = ShapeFactory::rectangleOutline(
        GRID_WINDOW_WIDTH,
        GRID_WINDOW_HEIGHT,
        GRID_WINDOW_OUTLINE_COLOR
    );
    Mesh* gridWindowMesh = gridWindowShape.convertToMesh("grid_window");
    AddMeshToList(gridWindowMesh);

    // Spaceship grid element
    Shape placementGridElement = ShapeFactory::square(
        PLACEMENT_GRID_ELEM_SIZE,
        PLACEMENT_GRID_COLOR
    );
    Mesh* placementGridMesh = placementGridElement.convertToMesh(
        "placement_grid_element"
    );
    AddMeshToList(placementGridMesh);

    // Spaceship center element of grid
    Shape placementGridCenterElement = ShapeFactory::square(
        PLACEMENT_GRID_ELEM_SIZE,
        PLACEMENT_GRID_COLOR_CENTER
    );
    Mesh* placementGridCenterMesh = placementGridCenterElement.convertToMesh(
        "placement_grid_element_center"
    );
    AddMeshToList(placementGridCenterMesh);

    // Available blocks display
    Shape availableBlockShape = ShapeFactory::square(
        AVAILABLE_BLOCK_LENGTH,
        AVAILABLE_BLOCK_COLOR
    );
    Mesh* availableBlockMesh = availableBlockShape.convertToMesh(
        "available_block"
    );
    AddMeshToList(availableBlockMesh);

    // Start button disabled
    Shape startButtonDisShape = StartButtonShape(START_BUTTON_DISABLED_COLOR);
    Mesh* startButtonDisMesh = startButtonDisShape.convertToMesh(
        "start_button_disabled"
    );
    AddMeshToList(startButtonDisMesh);

    // Start button enabled
    Shape startButtonEnaShape = StartButtonShape(START_BUTTON_ENABLED_COLOR);
    Mesh* startButtonEnaMesh = startButtonEnaShape.convertToMesh(
        "start_button_enabled"
    );
    AddMeshToList(startButtonEnaMesh);

    // Upgrade button
    Shape upgradeButtonShape = ArrowShape(
        UPGRADE_ARROW_LINE_WIDTH,
        UPGRADE_ARROW_LINE_HEIGHT,
        UPGRADE_ARROW_TIP_WIDTH,
        UPGRADE_ARROW_TIP_HEIGHT,
        UPGRADE_BUTTON_COLOR
    );
    Mesh* upgradeButtonMesh = upgradeButtonShape.convertToMesh("upgrade_button");
    AddMeshToList(upgradeButtonMesh);
}

void AvisStrikeScene::Init()
{
    // Setup the camera
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(
        0, (float)resolution.x, 
        0, (float)resolution.y, 
        0.01f, 400
    );
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Initialize the meshes
    initializeMeshes();

    // Seed the randomizer with current time
    srand(time(NULL));

    // Initialize placeable components
    // Put the component windows
    for (size_t i = 0; i < AVAILABLE_COMPONENT_TYPES; i++) {
        componentWindows.emplace_back(
            "component_window", 
            COMPONENT_WINDOW_WIDTH,
            COMPONENT_WINDOW_HEIGHT
        );
        glm::vec2 pos = {
            0.01f + COMPONENT_WINDOW_WIDTH / 2.f,
            (i + 0.51f) * COMPONENT_WINDOW_HEIGHT
        };
        componentWindows[i].setPosition(pos);
    }

    // Put the placeable components
    placeableComponents.emplace_back(
        "solid_block", 
        TILE_LENGTH, 
        TILE_LENGTH, 
        TILES_EDITOR_SCALE
    );
    placeableComponents.back().setPosition(componentWindows[0].getPosition());

    placeableComponents.emplace_back(
        "engine", 
        TILE_LENGTH, 
        TILE_LENGTH, 
        TILES_EDITOR_SCALE
    );
    placeableComponents.back().setPosition(componentWindows[1].getPosition());

    placeableComponents.emplace_back(
        "turret", 
        TILE_LENGTH, 
        TILE_LENGTH, 
        TILES_EDITOR_SCALE
    );
    glm::vec2 turretPos = componentWindows[2].getPosition();
    turretPos.y -= 2.f * TILE_LENGTH;
    placeableComponents.back().setPosition(turretPos);

    // Put the upgrade buttons
    engineUpgradeBtn = EditorUIElement(
        "upgrade_button",
        UPGRADE_BUTTON_WIDTH,
        UPGRADE_BUTTON_HEIGHT
    );
    turretUpgradeBtn = engineUpgradeBtn;
    
    glm::vec2 engineUpgradePos = componentWindows[1].getPosition();
    engineUpgradePos.x += COMPONENT_WINDOW_WIDTH * 0.375f;
    engineUpgradeBtn.setPosition(engineUpgradePos);

    glm::vec2 turretUpgradePos = componentWindows[2].getPosition();
    turretUpgradePos.x += COMPONENT_WINDOW_WIDTH * 0.375f;
    turretUpgradeBtn.setPosition(turretUpgradePos);

    // Initialize editor grid
    glm::vec2 gridCorner = {
        COMPONENT_WINDOW_WIDTH + 2.f * TILE_LENGTH_EDITOR,
        componentWindows[2].getPosition().y + TILE_LENGTH_EDITOR
    };

    // Put the grid window
    gridWindow = EditorUIElement(
        "grid_window",
        GRID_WINDOW_WIDTH,
        GRID_WINDOW_HEIGHT
    );
    glm::vec2 gridWindowPos = {
        gridCorner.x - TILE_LENGTH_EDITOR + GRID_WINDOW_WIDTH / 2.f,
        gridCorner.y + TILE_LENGTH_EDITOR - GRID_WINDOW_HEIGHT / 2.f
    };
    gridWindow.setPosition(gridWindowPos);

    // Put the placement markers
    for (size_t row = 0; row < SPACESHIP_GRID_ROWS; row++) {
        for (size_t col = 0; col < SPACESHIP_GRID_COLS; col++) {
            if (row == SPACESHIP_GRID_ROWS / 2 &&
                col == SPACESHIP_GRID_COLS / 2) {
                placementGrid.at(row, col) = EditorUIElement(
                    "placement_grid_element_center",
                    PLACEMENT_GRID_ELEM_SIZE,
                    PLACEMENT_GRID_ELEM_SIZE
                );
            }
            else {
                placementGrid.at(row, col) = EditorUIElement(
                    "placement_grid_element",
                    PLACEMENT_GRID_ELEM_SIZE,
                    PLACEMENT_GRID_ELEM_SIZE
                );
            }
            
            glm::vec2 pos = gridCorner;
            pos.x += col * TILE_LENGTH_EDITOR;
            pos.y -= row * TILE_LENGTH_EDITOR;
            placementGrid.at(row, col).setPosition(pos);
        }
    }

    // Initialize available blocks display
    glm::vec2 availableBlocksPos = {
        gridCorner.x - TILE_LENGTH_EDITOR,
        gridCorner.y + 3.f * TILE_LENGTH_EDITOR
    };
    for (size_t i = 0; i < MAX_SPACESHIP_BLOCKS; i++) {
        availableBlocksDisplay.emplace_back(
            "available_block",
            AVAILABLE_BLOCK_LENGTH,
            AVAILABLE_BLOCK_LENGTH
        );
        glm::vec2 pos = availableBlocksPos;
        pos.x += i * AVAILABLE_BLOCK_SPACING * TILE_LENGTH_EDITOR;
        availableBlocksDisplay.back().setPosition(pos);
    }

    // Initialize start buttons

    // By default, the empty spaceship is invalid
    isSpaceshipValid = false;
    dragging = false;
    draggedBlockType = SpaceshipBlock::NONE;
    
    glm::vec2 startButtonPos = availableBlocksPos;
    startButtonPos.x += MAX_SPACESHIP_BLOCKS * AVAILABLE_BLOCK_SPACING
        * TILE_LENGTH_EDITOR;

    // Put disabled start button
    disabledStatButton = EditorUIElement(
        "start_button_disabled",
        AVAILABLE_BLOCK_LENGTH,
        AVAILABLE_BLOCK_LENGTH
    );
    disabledStatButton.setPosition(startButtonPos);

    // Put enabled start button
    enabledStartButton = EditorUIElement(
        "start_button_enabled",
        AVAILABLE_BLOCK_LENGTH,
        AVAILABLE_BLOCK_LENGTH
    );
    enabledStartButton.setPosition(startButtonPos);
 
    // Initialize the HUD text renderer
    HUDRenderer = std::make_unique<gfxc::TextRenderer>(
        window->props.selfDir, 
        resolution.x, 
        resolution.y
    );

    HUDRenderer->Load(
        PATH_JOIN(
            window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"
        ), 
        HUD_TEXT_SIZE
    );

    // And the middle text renderer
    MiddleTextRenderer = std::make_unique<gfxc::TextRenderer>(
        window->props.selfDir,
        resolution.x,
        resolution.y
    );

    MiddleTextRenderer->Load(
        PATH_JOIN(
            window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"
        ),
        MIDDLE_TEXT_SIZE
    );

    
    // Pre-allocate game entities arrays
    chickens.reserve(CHICKEN_COUNT);
    eggs.reserve(3 * CHICKEN_COUNT);
    projectiles.reserve(CHICKEN_COUNT);

    // Start the game in editor mode
    currentState = GameState::EDITOR;

    // Initialize player variables
    money = 0;
    engineLevel = 1;
    turretLevel = 1;
    updateEditorText();
}

void AvisStrikeScene::drawEntity(const Entity& entity)
{
    RenderMesh2D(
        meshes[entity.getMeshName()],
        shaders["VertexColor"],
        entity.getModelMatrix()
    );
}

void AvisStrikeScene::drawUIElement(const EditorUIElement& element)
{
    RenderMesh2D(
        meshes[element.getMeshName()],
        shaders["VertexColor"],
        element.getModelMatrix()
    );
}

void AvisStrikeScene::drawEditor()
{
    // Draw the dragged block
    if (dragging) {
        drawUIElement(draggedBlock);
    }

    // Draw placeable components
    for (size_t i = 0; i < AVAILABLE_COMPONENT_TYPES; i++) {
        drawUIElement(componentWindows[i]);
        drawUIElement(placeableComponents[i]);
    }

    // Draw placed components
    for (size_t i = 0; i < placedComponents.size(); i++) {
        drawUIElement(placedComponents[i].uiElement);
    }

    // Draw the upgrade buttons if the upgrades are possible
    if (money - getUpgradeCost(engineLevel) >= 0) {
        drawUIElement(engineUpgradeBtn);
    }
    if (money - getUpgradeCost(turretLevel) >= 0) {
        drawUIElement(turretUpgradeBtn);
    }

    // Draw current money and components with their levels and update costs
    drawEditorText();
    
    // Draw editor grid
    drawUIElement(gridWindow);
    for (size_t i = 0; i < SPACESHIP_GRID_ROWS; i++) {
        for (size_t j = 0; j < SPACESHIP_GRID_COLS; j++) {
            drawUIElement(placementGrid.at(i, j));
        }
    }

    // Draw available blocks
    for (size_t i = 0; i < spaceshipData.getAvailableBlocks(); i++) {
        drawUIElement(availableBlocksDisplay[i]);
    }

    // Draw start button
    if (isSpaceshipValid) {
        drawUIElement(enabledStartButton);
    }
    else {
        drawUIElement(disabledStatButton);
    }
}

void AvisStrikeScene::resetGame()
{
    // Reset the score and the wave
    currentScore = 0;
    currentWave = 1;

    // Clear whatever was previously on the map
    chickens.clear();
    eggs.clear();
    projectiles.clear();

    // Construct the spaceship
    spaceship = std::make_unique<Spaceship>(
        spaceshipData, 
        SPACESHIP_SPAWN_POINT,
        engineLevel,
        turretLevel
    );

    // Initialize the new wave
    initializeWave();
}

void AvisStrikeScene::initializeWave()
{   
    currentState = GameState::PLAYING;
    projectiles.clear();

    // Initialize properties according to the current wave
    ChickenProperties properties(currentWave);

    // Spawn the chicken
    glm::vec2 firstChickenPos = { 
        SCREEN_WIDTH / 2.f - 2.f * ChickenShape::getWidth(),
        SCREEN_HEIGHT + (0.25f + 2.f) * ChickenShape::getHeight() 
        // the 2.f is to place the chickens up for the entrance animation
    };
    glm::vec2 chickenSpacing = { ChickenShape::getWidth() , 0.f };

    // First row should oscillate in one direction
    // The second one in the opposite direction
    bool reverseOscillation = (currentWave % 2 == 0);

    for (size_t i = 0; i < CHICKEN_COUNT; i++) {
        // After populating a line, go downwards and
        // reverse the oscillation direction
        if (i % CHICKEN_PER_LINE == 0) {
            firstChickenPos.y -= ChickenShape::getHeight();
            reverseOscillation = !reverseOscillation;
        }

        glm::vec2 posOffset = chickenSpacing * (float)(i % CHICKEN_PER_LINE);
        glm::vec2 initialPos = firstChickenPos + posOffset;

        chickens.emplace_back(initialPos, properties, reverseOscillation);
    }

    // Update the HUD
    updateHUDText();
}

void AvisStrikeScene::updateGame(float deltaTimeSeconds)
{
    // Process spaceship
    spaceship->update(deltaTimeSeconds);

    // Process the projectiles
    for (size_t i = 0; i < projectiles.size(); i++) {
        projectiles[i].update(deltaTimeSeconds);

        // Kill the chickens with which it collides
        for (size_t j = 0; j < chickens.size(); j++) {
            if (Entity::collide(projectiles[i], chickens[j])) {
                chickens[j].kill();
                projectiles[i].despawn();
            }
        }

        // Do the same for eggs
        for (size_t j = 0; j < eggs.size(); j++) {
            if (Entity::collide(projectiles[i], eggs[j])) {
                eggs[j].despawn();
                projectiles[i].despawn();
            }
        }

        // Remove despawned projectiles
        if (projectiles[i].hasDespawned()) {
            deleteSwapAndPop(projectiles, i--);
        }
    }

    // Process chickens
    for (size_t i = 0; i < chickens.size(); i++) {
        chickens[i].update(deltaTimeSeconds);

        // Spawn the eggs if they are due to fire
        if (chickens[i].fireIfDue()) {
            eggs.emplace_back(chickens[i].getEggSpeed());
            eggs.back().setPosition(chickens[i].getPosition());
        }

        // If a chicken touches the spaceship, game over
        if (spaceship->collide(chickens[i])) {
            setGameOver();
        }

        // If a chicken touches the bottom, game over
        if (chickens[i].getPosition().y < 3.f * ChickenShape::getHeight() / 8.f) {
            setGameOver();
        }

        // Remove dead chickens
        if (chickens[i].isDead()) {
            deleteSwapAndPop(chickens, i--);

            // Give a point for each dead chicken
            currentScore++;

            // And money ($1 for each wave)
            money += currentWave;

            // Update the HUD
            updateHUDText();
        }
    }

    // Decrease wave cleared delay if it's cleared
    if (currentState == GameState::WAVE_CLEARED) {
        waveClearedTimer -= deltaTimeSeconds;

        // Go to the next wave if the time passed
        if (waveClearedTimer <= 0.f) {
            currentWave++;
            initializeWave();
        }
    }

    // Switch to wave cleared if no more chickens are alive
    if (chickens.empty() && currentState == GameState::PLAYING) {
        currentState = GameState::WAVE_CLEARED;
        waveClearedTimer = NEXT_WAVE_DELAY;
        updateMiddleText();
    }

    // Process eggs
    for (size_t i = 0; i < eggs.size(); i++) {
        eggs[i].update(deltaTimeSeconds);

        // Check if eggs hit the spaceship
        if (spaceship->collide(eggs[i])) {
            setGameOver();
            eggs[i].despawn();
        }

        // Remove despawned eggs
        if (eggs[i].hasDespawned()) {
            deleteSwapAndPop(eggs, i--);
        }
    }
}

void AvisStrikeScene::updateHUDText()
{
    std::ostringstream ss;
    ss << std::left << std::setfill(' ');

    ss << "Score: " << std::setw(HUD_SPACING) << currentScore;
    ss << "Money: $" << std::setw(HUD_SPACING - 1) << money;
    ss << "Wave: " << std::setw(HUD_SPACING) << currentWave;
    ss << "Chickens: " << std::setw(HUD_SPACING) << chickens.size();

    HUDText = ss.str();
}

void AvisStrikeScene::updateMiddleText()
{
    // Determine the size in pixels of the characters
    glm::vec2 charSize = {
        MIDDLE_TEXT_SIZE * TEXT_WIDTH_FACTOR,
        MIDDLE_TEXT_SIZE * TEXT_HEIGHT_FACTOR
    };

    // Set the corresponding string and color, depending on the state
    switch (currentState) {
    case GameState::PAUSED:
        middleText = "PAUSED";
        middleTextColor = GAME_PAUSED_TEXT_COLOR;
        break;

    case GameState::GAME_OVER:
        middleText = "GAME OVER";
        middleTextColor = GAME_OVER_TEXT_COLOR;
        break;

    case GameState::WAVE_CLEARED:
        middleText = "WAVE " + std::to_string(currentWave) + " DEFEATED";
        middleTextColor = WAVE_CLEARED_TEXT_COLOR;
        break;

    default:
        middleText = "";
    }

    // Put the text centered on the screen
    float textLen = middleText.length();
    middleTextPos.x = SCREEN_WIDTH / 2.f - charSize.x * textLen / 2.f;
    middleTextPos.y = SCREEN_HEIGHT / 2.f - charSize.y / 2.f;
}

void AvisStrikeScene::drawMiddleText()
{
    MiddleTextRenderer->RenderText(
        middleText, 
        middleTextPos.x, 
        middleTextPos.y, 
        1.f, 
        middleTextColor
    );
}

void AvisStrikeScene::updateEditorText()
{
    moneyDisplayEditor = "Money: $" + std::to_string(money);

    engineUpgradeDisplay = "ENGINE: level " + std::to_string(engineLevel)
        + " (upgrade cost $" + std::to_string(getUpgradeCost(engineLevel)) + ")";

    turretUpgradeDisplay = "TURRET: level " + std::to_string(turretLevel)
        + " (upgrade cost $" + std::to_string(getUpgradeCost(turretLevel)) + ")";
}

void AvisStrikeScene::drawEditorText()
{
    float yPos = 1.5f * AVAILABLE_BLOCK_LENGTH + HUD_POS.y;

    // Display money
    HUDRenderer->RenderText(moneyDisplayEditor, HUD_POS.x, yPos, 1.f, HUD_TEXT_COLOR);
    yPos += HUD_TEXT_SIZE;

    // Display engine level and update cost
    HUDRenderer->RenderText(engineUpgradeDisplay, HUD_POS.x, yPos, 1.f, HUD_TEXT_COLOR);
    yPos += HUD_TEXT_SIZE;

    // Display turret level and update cost
    HUDRenderer->RenderText(turretUpgradeDisplay, HUD_POS.x, yPos, 1.f, HUD_TEXT_COLOR);
}

void AvisStrikeScene::drawGame()
{
    // Draw the spaceship if not game over
    if (currentState != GameState::GAME_OVER) {
        for (const auto& entity : spaceship->getEntities()) {
            drawEntity(*entity);
        }
    }

    // Draw the projectiles
    for (size_t i = 0; i < projectiles.size(); i++) {
        drawEntity(projectiles[i]);
    }

    // Draw the chickens
    for (size_t i = 0; i < chickens.size(); i++) {
        drawEntity(chickens[i]);
    }

    // Draw the eggs
    for (size_t i = 0; i < eggs.size(); i++) {
        drawEntity(eggs[i]);
    }

    // Draw the HUD text
    HUDRenderer->RenderText(HUDText, HUD_POS.x, HUD_POS.y, 1.f, HUD_TEXT_COLOR);
}

void AvisStrikeScene::setGameOver()
{
    currentState = GameState::GAME_OVER;
    updateMiddleText();
}

void AvisStrikeScene::FrameStart()
{
    // Set the clear color
    glClearColor(
        BACKGROUND_COLOR.r,
        BACKGROUND_COLOR.g,
        BACKGROUND_COLOR.b,
        1.f
    );

    // Clear the color buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void AvisStrikeScene::Update(float deltaTimeSeconds)
{
    switch (currentState) {
    case GameState::EDITOR:
        drawEditor();
        break;

    case GameState::PLAYING:
        updateGame(deltaTimeSeconds);
        drawGame();
        break;

    case GameState::WAVE_CLEARED:
        updateGame(deltaTimeSeconds);
        drawGame();
        drawMiddleText();

    case GameState::PAUSED:
    case GameState::GAME_OVER:
        drawGame();
        drawMiddleText();
        break;

    default:
        break;
    }
}


void AvisStrikeScene::FrameEnd()
{
}

void AvisStrikeScene::OnInputUpdate(float deltaTime, int mods)
{
    switch (currentState) {
    case GameState::PLAYING:
    case GameState::WAVE_CLEARED:
        // Process spaceship movement
        constexpr glm::vec2 upDirection = { 0.f, 1.f };
        constexpr glm::vec2 downDirection = { 0.f, -1.f };
        constexpr glm::vec2 leftDirection = { -1.f, 0.f };
        constexpr glm::vec2 rightDirection = { 1.f, 0.f };

        // Up
        glm::vec2 pos = spaceship->getPosition();
        if (window->KeyHold(GLFW_KEY_UP) || window->KeyHold(GLFW_KEY_W)) {
            if (pos.y < SCREEN_HEIGHT - spaceship->getHeight() / 2.f) {
                spaceship->move(upDirection, deltaTime);
            }
        }

        // Down
        if (window->KeyHold(GLFW_KEY_DOWN) || window->KeyHold(GLFW_KEY_S)) {
            if (pos.y > spaceship->getHeight() / 2.f) {
                spaceship->move(downDirection, deltaTime);
            } 
        }

        // Left
        if (window->KeyHold(GLFW_KEY_LEFT) || window->KeyHold(GLFW_KEY_A)) {
            if (pos.x > spaceship->getWidth() / 2.f) {
                spaceship->move(leftDirection, deltaTime);
            }
        }

        // Right
        if (window->KeyHold(GLFW_KEY_RIGHT) || window->KeyHold(GLFW_KEY_D)) {
            if (pos.x < SCREEN_WIDTH - spaceship->getWidth() / 2.f) {
                spaceship->move(rightDirection, deltaTime);
            }
        }

        // Process turret firing
        if (window->KeyHold(GLFW_KEY_SPACE)) {
            for (auto& turret : spaceship->getTurrets()) {
                if (turret->fireIfAble()) {
                    glm::vec2 projectileSpeed = PROJECTILE_SPEED_BASE
                        + (float)turretLevel * PROJECTILE_SPEED_PER_LEVEL;

                    projectiles.emplace_back(projectileSpeed);

                    glm::vec2 spawnPos = turret->getPosition();
                    spawnPos.y += 2 * TILE_LENGTH;
                    projectiles.back().setPosition(spawnPos);
                }
            }
        }
    }
}

void AvisStrikeScene::OnKeyPress(int key, int mods)
{
    // Use P to toggle between playing and paused states
    if (key == GLFW_KEY_P) {
        if (currentState == GameState::PLAYING) {
            currentState = GameState::PAUSED;
            updateMiddleText();
        }
        else if (currentState == GameState::PAUSED) {
            currentState = GameState::PLAYING;
        }
    }

    // Use R to go back to editor from game over
    if (key == GLFW_KEY_R) {
        if (currentState == GameState::GAME_OVER) {
            currentState = GameState::EDITOR;
            updateEditorText();
        }
    }
}


void AvisStrikeScene::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

glm::vec2 AvisStrikeScene::getWorldMousePos(int mouseX, int mouseY)
{
    // Gets world coordinates regardless how the window is resized
    glm::ivec2 resolution = window->GetResolution(true);

    glm::vec2 scale = {
        (float)SCREEN_WIDTH / resolution.x,
        (float)SCREEN_HEIGHT / resolution.y
    };
    return { scale.x * mouseX, scale.y * (resolution.y - mouseY)};
}

void AvisStrikeScene::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // If dragging, move the dragged component to the cursor
    if (currentState == GameState::EDITOR && dragging) {
        draggedBlock.setPosition(getWorldMousePos(mouseX, mouseY));
    }
}

#define LEFT_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 2

void AvisStrikeScene::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::vec2 mousePos = getWorldMousePos(mouseX, mouseY);

    // Process clicking the update buttons
    if (currentState == GameState::EDITOR && button == LEFT_MOUSE_BUTTON) {
        if (money >= getUpgradeCost(engineLevel) &&
            engineUpgradeBtn.pointIsContained(mousePos)) {

            money -= getUpgradeCost(engineLevel);
            engineLevel++;
            updateEditorText();
        }

        if (money >= getUpgradeCost(turretLevel) &&
            turretUpgradeBtn.pointIsContained(mousePos)) {

            money -= getUpgradeCost(turretLevel);
            turretLevel++;
            updateEditorText();
        }
    }

    // Process starting the drag
    if (currentState == GameState::EDITOR && !dragging && 
        button == LEFT_MOUSE_BUTTON) {
        size_t i;
        for (i = 0; i < AVAILABLE_COMPONENT_TYPES; i++) {
            if (componentWindows[i].pointIsContained(mousePos)) {
                draggedBlock = placeableComponents[i];
                dragging = true;
                break;
            }
        }
        if (dragging) {
            draggedBlockType = SpaceshipBlock(i);
        }
    }

    // Process right clicking on blocks to remove them
    if (currentState == GameState::EDITOR && button == RIGHT_MOUSE_BUTTON) {
        for (size_t i = 0; i < placedComponents.size(); i++) {
            if (!placedComponents[i].uiElement.pointIsContained(mousePos)) {
                continue;
            }
            
            spaceshipData.removeBlock(
                placedComponents[i].row,
                placedComponents[i].col
            );
            deleteSwapAndPop(placedComponents, i);

            isSpaceshipValid = spaceshipData.isValid();
            break;
        }
    }

    // Process clicking the start button
    if (currentState == GameState::EDITOR && button == LEFT_MOUSE_BUTTON &&
        isSpaceshipValid && enabledStartButton.pointIsContained(mousePos)) {
        resetGame();
        currentState = GameState::PLAYING;
    }
}

void AvisStrikeScene::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Process releasing dragged element
    if (currentState == GameState::EDITOR && dragging) {
        dragging = false;
        glm::vec2 mousePos = getWorldMousePos(mouseX, mouseY);
        for (size_t row = 0; row < SPACESHIP_GRID_ROWS; row++) {
            for (size_t col = 0; col < SPACESHIP_GRID_COLS; col++) {
                // Continue until we check if the mouse is on the given tile
                if (!placementGrid.at(row, col).pointIsContained(mousePos)) {
                    continue;
                }

                // Try to place the block where we have the mouse over
                bool canPlace = spaceshipData.addBlock(row, col, draggedBlockType);
                
                // If failed, stop iterating
                if (!canPlace) {
                    draggedBlockType = SpaceshipBlock::NONE;
                    break;
                }

                // If we can, add a visual with the block in the editor
                placedComponents.emplace_back(
                    placeableComponents[static_cast<int>(draggedBlockType)],
                    row, col
                );
                glm::vec2 pos = placementGrid.at(row, col).getPosition();
                placedComponents.back().uiElement.setPosition(pos);
                    
                // Clear the dragged block and check if spaceship is valid
                draggedBlockType = SpaceshipBlock::NONE;
                isSpaceshipValid = spaceshipData.isValid();
                break;
            }

            // If attempted to place a block, stop iterating
            if (draggedBlockType == SpaceshipBlock::NONE) {
                break;
            }
        }
    }
}


void AvisStrikeScene::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void AvisStrikeScene::OnWindowResize(int width, int height)
{
}

int AvisStrikeScene::getUpgradeCost(int level)
{
    return UPGRADE_COST_PER_LEVEL * level;
}
