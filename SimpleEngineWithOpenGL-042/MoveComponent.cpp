#include "MoveComponent.h"
#include "Actor.h"
#include "Maths.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrder) :
	Component(ownerP, updateOrder),
	angularSpeed(0.0f),
	forwardSpeed(0.0f)
{
}

void MoveComponent::update(float deltaTime)
{
	if (!Maths::nearZero(forwardSpeed))
	{
		Vector3 position = owner.getPosition();
		position += forwardDirection * forwardSpeed * deltaTime;
		owner.setPosition(position);
	}

	if (!Maths::nearZero(angularSpeed))
	{
		Quaternion rotation = owner.getRotation();
		float angle = angularSpeed * deltaTime;
		Quaternion incrementalRotation(Vector3::unitZ, angle);
		rotation = Quaternion::concatenate(rotation, incrementalRotation);
		owner.setRotation(rotation);
	}
}

void MoveComponent::setForwardSpeed(float speed)
{
	forwardSpeed = speed;
}

void MoveComponent::setAngularSpeed(float speed)
{
	angularSpeed = speed;
}

void MoveComponent::setForwardDirection(const Vector3& direction)
{
	forwardDirection = direction;
}
