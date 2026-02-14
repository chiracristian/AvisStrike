#pragma once

#include "Entity.h"

class SolidBlock : public Entity
{
public:
	SolidBlock();
	void update(float deltaTimeSeconds) override;

private:
	
};