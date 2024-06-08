#pragma once
#include "Actor.h"
#include "Vector3.h"
#include "AABB.h"

class FPSActor : public Actor
{
public:
	FPSActor();
	void resolveCollision(const AABB& playerBox, const AABB& otherBox, Vector3& pos);
	
	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;
	void shoot();
	
	void setFootstepSurface(float value);
	void setVisible(bool isVisible);
	void setEnd(bool pendGame);
	void fixCollisions();
	int getHP(){return hp;}
	bool getEnd(){return endGame;}

	void setHP(int php);
	void damage();

private:
	class MoveComponent* moveComponent;
	class AudioComponent* audioComponent;
	class MeshComponent* meshComponent;
	class FPSCameraComponent* cameraComponent;
	class Actor* FPSModel;
	float lastFootstep;
	class BoxComponent* boxComponent;
	int hp = 3;
	bool endGame = false;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);
