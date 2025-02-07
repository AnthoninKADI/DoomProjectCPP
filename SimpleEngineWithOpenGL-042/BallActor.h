#pragma once
#include "Actor.h"
class BallMoveComponent;

class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void hitTarget();
	BallMoveComponent* getMoveComponent() const;

private:
	class AudioComponent* audio;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
};

