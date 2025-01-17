#pragma once
#include "MoveComponent.h"
#include <SDL_scancode.h> // Ajout pour SDL_Scancode

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* ownerP);

	void processInput(const struct InputState& inputState) override;

	// Définit les clés pour le contrôle
	void setForwardKey(SDL_Scancode key) { forwardKey = key; }
	void setBackKey(SDL_Scancode key) { backKey = key; }
	void setClockwiseKey(SDL_Scancode key) { clockwiseKey = key; }
	void setCounterClockwiseKey(SDL_Scancode key) { counterClockwiseKey = key; }

private:
	float maxForwardSpeed;
	float maxAngularSpeed;

	SDL_Scancode forwardKey;
	SDL_Scancode backKey;
	SDL_Scancode clockwiseKey;
	SDL_Scancode counterClockwiseKey;
};
