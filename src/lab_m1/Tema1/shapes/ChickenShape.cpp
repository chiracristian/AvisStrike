#include "ChickenShape.h"
#include "ShapeFactory.h"
#include "../transform2D.h"

constexpr float FEET_WIDTH = 0.15f * CHICKEN_BODY_LENGTH;
constexpr float FEET_HEIGHT = 2.f * FEET_WIDTH;
constexpr float FEET_BODY_ATTACH_FRAC = 0.9f;

constexpr float WING_LENGTH = 0.8f * CHICKEN_BODY_LENGTH;
constexpr float WING_BODY_ATTACH_FRAC = 0.7f;
constexpr float WING_ANGLE_LEFT = 15.f;
constexpr float WING_ANGLE_RIGHT = 25.f;

constexpr float HEAD_RADIUS = 0.7f * CHICKEN_BODY_LENGTH / 2.f;
constexpr float HEAD_BODY_ATTACH_FRAC = 0.95f;

constexpr float CREST_WIDTH = HEAD_RADIUS / 2.f;
constexpr float CREST_1_HEIGHT = CREST_WIDTH * 1.5f;
constexpr float CREST_2_HEIGHT = CREST_WIDTH * 2.f;

constexpr float BEAK_LEFT_X = -HEAD_RADIUS / 2.f;
constexpr float BEAK_LEFT_Y = 0.f;
constexpr float BEAK_RIGHT_X = HEAD_RADIUS * 5.f / 8.f;
constexpr float BEAK_RIGHT_Y = -HEAD_RADIUS / 4.f;
constexpr float BEAK_TOP_X = 0.f;
constexpr float BEAK_TOP_Y = HEAD_RADIUS * 3.f / 8.f;

constexpr float EYE_RADIUS = HEAD_RADIUS / 8.f;
constexpr float EYE_LEFT_X = BEAK_LEFT_X;
constexpr float EYE_LEFT_Y = BEAK_TOP_Y;

constexpr float EYE_RIGHT_X = 1.5f * BEAK_RIGHT_X / 2.f;
constexpr float EYE_RIGHT_Y = EYE_LEFT_Y + EYE_RADIUS;

constexpr glm::vec3 BODY_COLOR = glm::vec3(0.058f, 0.529f, 1.f);
constexpr glm::vec3 BEAK_COLOR = glm::vec3(1.f, 0.5f, 0.105f);
constexpr glm::vec3 WING_COLOR = glm::vec3(0.7f, 0.7f, 0.7f);
constexpr glm::vec3 CREST_COLOR = glm::vec3(0.9f, 0.067f, 0.058f);
constexpr glm::vec3 EYE_COLOR = glm::vec3(0.f, 0.f, 0.f);

ChickenShape::ChickenShape(unsigned drawMode)
{
	// Build the body
	Shape body = ShapeFactory::square(CHICKEN_BODY_LENGTH, BODY_COLOR);

	// Build the legs
	Shape rightLeg = ShapeFactory::rectangle(
		FEET_WIDTH, 
		FEET_HEIGHT,
		BEAK_COLOR);

	glm::vec2 legPos(0.f);
	legPos.x = CHICKEN_BODY_LENGTH / 4.f;
	legPos.y = (-FEET_BODY_ATTACH_FRAC * CHICKEN_BODY_LENGTH - FEET_HEIGHT) / 2.f;
	rightLeg.applyTransform(transf2D::translate(legPos.x, legPos.y));

	Shape leftLeg = rightLeg;
	leftLeg.applyTransform(transf2D::flipHorizontal());

	// Build the feet
	glm::vec2 footLeftCorner = legPos;
	footLeftCorner.x -= FEET_WIDTH / 2.f;
	footLeftCorner.y -= FEET_HEIGHT / 2.f;

	glm::vec2 footRightCorner = footLeftCorner;
	footLeftCorner.x += FEET_HEIGHT;

	glm::vec2 footBottom(0.f);
	footBottom.x = (footLeftCorner.x + footRightCorner.x) / 2.f;
	footBottom.y = footLeftCorner.y - FEET_HEIGHT / 2.f;

	Shape rightFoot = ShapeFactory::triangle(
		footBottom,
		footRightCorner,
		footLeftCorner,
		BEAK_COLOR);

	Shape leftFoot = rightFoot;
	leftFoot.applyTransform(transf2D::flipHorizontal());

	// Build the wings
	glm::vec2 wingBottomCorner(0.f);
	glm::vec2 wingRightAngle(WING_LENGTH, 0.f);
	glm::vec2 wingTopCorner(WING_LENGTH, WING_LENGTH);

	Shape rightWing = ShapeFactory::triangle(
		wingBottomCorner,
		wingRightAngle,
		wingTopCorner,
		WING_COLOR);

	Shape leftWing = rightWing;

	rightWing.applyTransform(transf2D::rotate(glm::radians(WING_ANGLE_RIGHT)));
	float rightWingPos = WING_BODY_ATTACH_FRAC * CHICKEN_BODY_LENGTH / 2.f;
	rightWing.applyTransform(transf2D::translate(rightWingPos, 0.f));

	leftWing.applyTransform(transf2D::rotate(glm::radians(WING_ANGLE_LEFT)));
	float leftWingPos = WING_BODY_ATTACH_FRAC * CHICKEN_BODY_LENGTH / 2.f;
	leftWing.applyTransform(transf2D::translate(leftWingPos, 0.f));
	leftWing.applyTransform(transf2D::flipHorizontal());

	// Build the head
	Shape head = ShapeFactory::circle(HEAD_RADIUS, WING_COLOR);
	float headHeight = HEAD_BODY_ATTACH_FRAC * CHICKEN_BODY_LENGTH / 2.f + HEAD_RADIUS;
	head.applyTransform(transf2D::translate(0.f, headHeight));

	// Build the crest
	glm::vec2 leftCrestsCorner(-CREST_WIDTH, 0.f);
	glm::vec2 crest1Top(0.f, CREST_1_HEIGHT);

	glm::vec2 rightCrestBottomCorner(CREST_WIDTH, 0.f);
	glm::vec2 rightCrestTopCorner(1.5f * CREST_WIDTH, CREST_2_HEIGHT);

	Shape crest1 = ShapeFactory::triangle(
		leftCrestsCorner,
		glm::vec2(0.f),
		crest1Top,
		CREST_COLOR
	);

	Shape crest2 = ShapeFactory::triangle(
		leftCrestsCorner,
		rightCrestBottomCorner,
		rightCrestTopCorner,
		CREST_COLOR
	);

	Shape crest = crest2;
	crest.merge(crest1);
	crest.applyTransform(transf2D::translate(0.f, headHeight + 0.9f * HEAD_RADIUS));

	// Build the beak
	glm::vec2 beakLeft(BEAK_LEFT_X, BEAK_LEFT_Y);
	glm::vec2 beakRight(BEAK_RIGHT_X, BEAK_RIGHT_Y);
	glm::vec2 beakTop(BEAK_TOP_X, BEAK_TOP_Y);

	Shape beak = ShapeFactory::triangle(beakLeft, beakRight, beakTop, BEAK_COLOR);
	beak.applyTransform(transf2D::translate(0.f, headHeight));

	// Build the eyes
	Shape eye = ShapeFactory::circle(EYE_RADIUS, EYE_COLOR);

	Shape leftEye = eye;
	leftEye.applyTransform(transf2D::translate(EYE_LEFT_X, headHeight + EYE_LEFT_Y));

	Shape rightEye = eye;
	rightEye.applyTransform(transf2D::translate(EYE_RIGHT_X, headHeight + EYE_RIGHT_Y));

	// Combine the shapes (first ones appear above the latters)
	this->merge(rightEye);
	this->merge(leftEye);

	this->merge(beak);
	this->merge(crest);
	this->merge(head);

	this->merge(leftWing);
	this->merge(rightWing);

	this->merge(leftFoot);
	this->merge(rightFoot);

	this->merge(leftLeg);
	this->merge(rightLeg);

	this->merge(body);
}

float ChickenShape::getWidth()
{
	static float computedValue = 0.f;

	if (computedValue == 0.f) {
		float leftWingSpan = WING_LENGTH * 
			std::cos(glm::radians(WING_ANGLE_LEFT)) * 0.75f;
		float rightWingSpan = WING_LENGTH * 
			std::cos(glm::radians(WING_ANGLE_RIGHT)) * 0.75f;
		float bodySpan = 2.f * WING_BODY_ATTACH_FRAC * CHICKEN_BODY_LENGTH;

		computedValue = leftWingSpan + bodySpan + rightWingSpan;
	}
	return computedValue;
}

float ChickenShape::getHeight()
{
	static float computedValue = 0.f;

	if (computedValue == 0.f) {
		float feetSpan = 1.5f * FEET_HEIGHT / 4.f;
		float bodySpan = (FEET_BODY_ATTACH_FRAC + HEAD_BODY_ATTACH_FRAC)
			* CHICKEN_BODY_LENGTH;
		float headSpan = HEAD_RADIUS;

		computedValue = feetSpan + bodySpan + headSpan;
	}

	return computedValue;
}

