#include "EngineShape.h"
#include "ShapeFactory.h"
#include "../transform2D.h"

#include <vector>

constexpr float ENGINE_BLOCK_LENGTH = TILE_LENGTH;

constexpr int NUM_SPIKES = 4;

constexpr float FIRE_LENGTH = 0.9f * TILE_LENGTH;
constexpr float FIRE_SPIKES_X[NUM_SPIKES] = { -1.f, -0.5f, 0.25f, 1.f};
constexpr float FIRE_SPIKES_Y[NUM_SPIKES] = { 0.9f, 1.f, 0.95f, 0.85f};

constexpr glm::vec3 ENGINE_BLOCK_COLOR = { 1.f, 0.6f, 0.f };
constexpr glm::vec3 FIRE_COLOR = { 1.f, 0.2f, 0.f };

EngineShape::EngineShape(unsigned drawMode)
{
	Shape engineBlock = ShapeFactory::square(ENGINE_BLOCK_LENGTH, ENGINE_BLOCK_COLOR);

	for (int i = 0; i < NUM_SPIKES; i++) {
		Shape fireTriangle = ShapeFactory::triangle(
			glm::vec2(-FIRE_LENGTH / 2.f, 0.f),
			glm::vec2(FIRE_SPIKES_X[i] * FIRE_LENGTH / 2.f, -FIRE_SPIKES_Y[i] * FIRE_LENGTH / 2.f),
			glm::vec2(FIRE_LENGTH / 2.f, 0.f),
			FIRE_COLOR
		);
		fireTriangle.applyTransform(transf2D::translate(0.f, -ENGINE_BLOCK_LENGTH / 2.f));
		this->merge(fireTriangle);
	}
	this->merge(engineBlock);
}
