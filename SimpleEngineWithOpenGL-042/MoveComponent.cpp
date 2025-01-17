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
		// Calcul de la nouvelle position
		Vector3 pos = owner.getPosition();
		Vector3 forward = owner.getForward();
		pos += forward * forwardSpeed * deltaTime;
		owner.setPosition(pos);
	}

	if (!Maths::nearZero(angularSpeed))
	{
		// Calcul de la nouvelle rotation
		Quaternion rot = owner.getRotation();
		float angle = angularSpeed * deltaTime;
		Quaternion inc(Vector3::unitZ, angle);
		rot = Quaternion::concatenate(rot, inc);
		owner.setRotation(rot);
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