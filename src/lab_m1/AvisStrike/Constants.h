#pragma once

#include "glm/vec3.hpp"

// General constants
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr glm::vec3 NORMAL = { 0.f, 0.f, 1.f };
constexpr unsigned CIRCLE_EDGE_COUNT = 30;
constexpr glm::vec3 BACKGROUND_COLOR = { 0.f, 0.f, 0.1f };

constexpr size_t MAX_SPACESHIP_BLOCKS = 10;
constexpr size_t SPACESHIP_GRID_ROWS = 9;
constexpr size_t SPACESHIP_GRID_COLS = 17;

// Game Graphics constants
constexpr float TEXT_WIDTH_FACTOR = 0.6f;
constexpr float TEXT_HEIGHT_FACTOR = 0.6f;

constexpr unsigned HUD_TEXT_SIZE = 20;
constexpr glm::vec3 HUD_TEXT_COLOR = { 1.f, 1.f, 1.f };
constexpr glm::vec2 HUD_POS = { 0.01f * SCREEN_WIDTH, 0.01f * SCREEN_HEIGHT };
constexpr int HUD_SPACING = 24;

constexpr float MIDDLE_TEXT_SIZE = 100;
constexpr glm::vec3 GAME_PAUSED_TEXT_COLOR = { 0.75f, 0.75f, 0.75f };
constexpr glm::vec3 GAME_OVER_TEXT_COLOR = { 1.f, 0.f, 0.f };
constexpr glm::vec3 WAVE_CLEARED_TEXT_COLOR = { 0.f, 1.f, 0.f };

constexpr float CHICKEN_BODY_LENGTH = 0.04f * SCREEN_WIDTH;

constexpr float TILE_LENGTH = 0.5f * CHICKEN_BODY_LENGTH;

constexpr float PROJECTILE_RADIUS = TILE_LENGTH / 4.f;
constexpr glm::vec3 PROJECTILE_COLOR = { 0.667f, 1.f, 0.439f };

constexpr float EGG_X_RADIUS = 0.15f * CHICKEN_BODY_LENGTH;
constexpr float EGG_Y_RADIUS = 0.225f * CHICKEN_BODY_LENGTH;
constexpr glm::vec3 EGG_COLOR = { 0.816f, 0.718f, 0.631f };

// Game mechanics constants
constexpr glm::vec2 SPACESHIP_SPAWN_POINT = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f };
constexpr float NEXT_WAVE_DELAY = 5.f;

constexpr float SPACESHIP_ENGINE_SPEED_PER_LEVEL = 50.f;

constexpr glm::vec2 PROJECTILE_SPEED_BASE = { 0.f, 50.f};
constexpr glm::vec2 PROJECTILE_SPEED_PER_LEVEL = { 0.f, 50.f };

constexpr float TURRET_FIRE_PERIOD_BASE = 1.1f;
constexpr float TURRET_FIRE_PERIOD_PER_LEVEL = 0.1f;
constexpr float TURRET_FIRE_PERIOD_MIN = 0.05f;

constexpr size_t CHICKEN_COUNT = 10;
constexpr size_t CHICKEN_PER_LINE = 5;

// Editor constants
constexpr float TILES_EDITOR_SCALE = 2.f;
constexpr float TILE_LENGTH_EDITOR = TILES_EDITOR_SCALE * TILE_LENGTH;
constexpr float COMPONENT_WINDOW_WIDTH = 0.2f * SCREEN_WIDTH;
constexpr float COMPONENT_WINDOW_HEIGHT = 0.25f * SCREEN_HEIGHT;
constexpr glm::vec3 COMPONENT_WINDOW_OUTLINE_COLOR = { 1.f, 0.f, 0.f };
constexpr size_t AVAILABLE_COMPONENT_TYPES = 3;

constexpr float GRID_WINDOW_WIDTH = TILE_LENGTH_EDITOR * (SPACESHIP_GRID_COLS + 1);
constexpr float GRID_WINDOW_HEIGHT = TILE_LENGTH_EDITOR * (SPACESHIP_GRID_ROWS + 1);
constexpr glm::vec3 GRID_WINDOW_OUTLINE_COLOR = { 0.f, 0.f, 1.f };

constexpr float PLACEMENT_GRID_ELEM_SIZE = 1.5f * TILE_LENGTH;
constexpr glm::vec3 PLACEMENT_GRID_COLOR = { 0.25f, 0.5f, 1.f };
constexpr glm::vec3 PLACEMENT_GRID_COLOR_CENTER = { 0.125f, 0.25f, 0.5f };

constexpr float AVAILABLE_BLOCK_LENGTH = TILE_LENGTH_EDITOR;
constexpr float AVAILABLE_BLOCK_SPACING = 1.75f;
constexpr glm::vec3 AVAILABLE_BLOCK_COLOR = { 0.153f, 0.618f, 0.f };

constexpr glm::vec3 START_BUTTON_DISABLED_COLOR = { 0.75f, 0.f, 0.f };
constexpr glm::vec3 START_BUTTON_ENABLED_COLOR = { 0.f, 0.75f, 0.f };

constexpr int UPGRADE_COST_PER_LEVEL = 10;

constexpr float UPGRADE_ARROW_LINE_WIDTH = HUD_TEXT_SIZE / 2.f;
constexpr float UPGRADE_ARROW_LINE_HEIGHT = 2.f * HUD_TEXT_SIZE;
constexpr float UPGRADE_ARROW_TIP_WIDTH = HUD_TEXT_SIZE;
constexpr float UPGRADE_ARROW_TIP_HEIGHT = HUD_TEXT_SIZE;

constexpr float UPGRADE_BUTTON_WIDTH = UPGRADE_ARROW_TIP_WIDTH;
constexpr float UPGRADE_BUTTON_HEIGHT = UPGRADE_ARROW_LINE_HEIGHT + UPGRADE_ARROW_TIP_HEIGHT;

constexpr glm::vec3 UPGRADE_BUTTON_COLOR = { 0.f, 1.f, 0.f };