#include "FPSCameraComponent.h"

FPSCameraComponent::FPSCameraComponent(Actor* ownerP):
	CameraComponent(ownerP),
	pitchSpeed(0.0f),
	maxPitch(Maths::pi / 3.0f),
	pitch(0.0f)
{
}

void FPSCameraComponent::update(float dt)
{
		CameraComponent::update(dt);
    
    	Vector3 cameraPosition = owner.getPosition();
    	pitch += -pitchSpeed * dt;
    	
    	pitch = Maths::clamp(pitch, -maxPitch, maxPitch);
    	
    	Quaternion pitchQuat = Quaternion(owner.getRight(), -pitch);
    	
    	Vector3 viewForward = Vector3::transform(Vector3::unitX, pitchQuat);
    	viewForward = Vector3::transform(viewForward, owner.getRotation());
    
    	Vector3 target = cameraPosition + viewForward * 100.0f;
    	Vector3 up = Vector3::transform(Vector3::unitZ, owner.getRotation());
    
    	Matrix4 view = Matrix4::createLookAt(cameraPosition, target, up);
    	setViewMatrix(view);
}

void FPSCameraComponent::setPitchSpeed(float speed)
{
	pitchSpeed = speed;
}

void FPSCameraComponent::setMaxPitch(float pitch)
{
	maxPitch = pitch;
}

Vector3 FPSCameraComponent::getForward() const
{
    	Quaternion pitchQuat(owner.getRight(), -pitch);
    	Vector3 forward = Vector3::transform(Vector3::unitX, owner.getRotation());
    	return Vector3::transform(forward, pitchQuat);  
}

void FPSCameraComponent::setPitch(float pitchValue)
{
	pitch = pitchValue;
}

