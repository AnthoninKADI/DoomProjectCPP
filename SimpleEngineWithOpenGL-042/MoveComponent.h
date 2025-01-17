#pragma once
#include "Component.h"
#include "Maths.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* ownerP, int updateOrder = 10);

	void update(float dt) override;

	void setForwardSpeed(float speed);
	void setAngularSpeed(float speed);

	// Ajout de getForwardSpeed
	float getForwardSpeed() const { return forwardSpeed; }

private:
	float forwardSpeed;   
	float angularSpeed;   
};