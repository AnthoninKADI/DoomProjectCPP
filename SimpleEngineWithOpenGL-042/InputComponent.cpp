#include "InputComponent.h"
#include "InputSystem.h"

InputComponent::InputComponent(Actor* ownerP) :
    MoveComponent(ownerP),
    maxForwardSpeed(300.0f),
    maxAngularSpeed(Maths::pi),
    forwardKey(SDL_SCANCODE_W),
    backKey(SDL_SCANCODE_S),
    clockwiseKey(SDL_SCANCODE_D),
    counterClockwiseKey(SDL_SCANCODE_Q)
{
}

void InputComponent::processInput(const InputState& inputState)
{
    // Gestion de la vitesse avant/arrière
    float forwardSpeed = 0.0f;
    if (inputState.keyboard.getKeyState(forwardKey) == ButtonState::Held)
    {
        forwardSpeed += maxForwardSpeed;
    }
    if (inputState.keyboard.getKeyState(backKey) == ButtonState::Held)
    {
        forwardSpeed -= maxForwardSpeed;
    }
    setForwardSpeed(forwardSpeed);

    // Gestion de la rotation gauche/droite
    float angularSpeed = 0.0f;
    if (inputState.keyboard.getKeyState(clockwiseKey) == ButtonState::Held)
    {
        angularSpeed -= maxAngularSpeed; 
    }
    if (inputState.keyboard.getKeyState(counterClockwiseKey) == ButtonState::Held)
    {
        angularSpeed += maxAngularSpeed; 
    }
    setAngularSpeed(angularSpeed);
}