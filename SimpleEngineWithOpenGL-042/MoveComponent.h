#pragma once
#include "Component.h"
#include "Maths.h"
#include "Vector3.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* ownerP, int updateOrder = 10);

	void update(float dt) override;

	void setForwardSpeed(float speed);
	void setAngularSpeed(float speed);

	void setForwardDirection(const Vector3& direction);
	float getForwardSpeed() const { return forwardSpeed; }

private:
	float forwardSpeed;   
	float angularSpeed;
	Vector3 forwardDirection;
};
