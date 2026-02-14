#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "components/text_renderer.h"

#include "EditorUIElement.h"
#include "entities/Chicken.h"
#include "entities/Egg.h"
#include "entities/Projectile.h"
#include "Spaceship.h"

namespace m1
{
    enum class GameState {
        EDITOR,
        PLAYING,
        PAUSED,
        WAVE_CLEARED,
        GAME_OVER
    };

    struct PlacedComponent {
        EditorUIElement uiElement;
        size_t row;
        size_t col;

        PlacedComponent(const EditorUIElement& uiElement, size_t row, size_t col)
        {
            this->uiElement = uiElement;
            this->row = row;
            this->col = col;
        }
    };

    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;
        

    private:
        void initializeMeshes();
        void drawEntity(const Entity& entity);

        void drawUIElement(const EditorUIElement& element);
        void drawEditor();

        void resetGame();
        void initializeWave();
        void updateGame(float deltaTimeSeconds);
        void drawGame();
        void setGameOver();

        void updateHUDText();
        void updateMiddleText();
        void drawMiddleText();
        void updateEditorText();
        void drawEditorText();

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        glm::vec2 getWorldMousePos(int mouseX, int mouseY);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        GameState currentState;
        float waveClearedTimer;

        std::unique_ptr<gfxc::TextRenderer> HUDRenderer;
        std::string HUDText;

        std::unique_ptr<gfxc::TextRenderer> MiddleTextRenderer;
        std::string middleText;
        glm::vec2 middleTextPos;
        glm::vec3 middleTextColor;
        
        // Editor variables
        SpaceshipData spaceshipData;
        bool isSpaceshipValid;
        bool dragging;
        SpaceshipBlock draggedBlockType;
        EditorUIElement draggedBlock;

        std::vector<EditorUIElement> componentWindows;
        std::vector<EditorUIElement> placeableComponents;
        std::vector<PlacedComponent> placedComponents;

        EditorUIElement gridWindow;
        Array2D<EditorUIElement> placementGrid;

        std::vector<EditorUIElement> availableBlocksDisplay;
        EditorUIElement disabledStatButton;
        EditorUIElement enabledStartButton;

        EditorUIElement engineUpgradeBtn;
        EditorUIElement turretUpgradeBtn;
        std::string moneyDisplayEditor;
        std::string engineUpgradeDisplay;
        std::string turretUpgradeDisplay;

        // Game variables
        int currentWave;
        int currentScore;
        std::unique_ptr<Spaceship> spaceship;
        std::vector<Projectile> projectiles;
        std::vector<Chicken> chickens;
        std::vector<Egg> eggs;

        // Player variables
        int money;
        int engineLevel;
        int turretLevel;
        int getUpgradeCost(int level);
    };
}   // namespace m1
