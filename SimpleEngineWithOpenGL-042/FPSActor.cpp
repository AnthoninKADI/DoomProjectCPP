#include "FPSActor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "BallActor.h"
#include "BallMoveComponent.h"
#include "BoxComponent.h"
#include "Collisions.h"

FPSActor::FPSActor() : 
    Actor(), 
    moveComponent(nullptr), 
    audioComponent(nullptr), 
    meshComponent(nullptr),
    cameraComponent(nullptr),
    lastFootstep(0.0f),
    boxComponent(nullptr)
{
    moveComponent = new MoveComponent(this);
    cameraComponent = new FPSCameraComponent(this);

    FPSModel = new Actor();
    FPSModel->setScale(Vector3(0.75f, 0.75f, 0.75f));
    meshComponent = new MeshComponent(FPSModel);
    // meshComponent->setMesh(Assets::getMesh("Mesh_Rifle"));

    boxComponent = new BoxComponent(this);
    AABB collision(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
    boxComponent->setObjectBox(collision);
    boxComponent->setShouldRotate(false);
}

void FPSActor::resolveCollision(const AABB& playerBox, const AABB& otherBox, Vector3& pos)
{
    // Calculate all our differences
    float dx1 = otherBox.max.x - playerBox.min.x;
    float dx2 = otherBox.min.x - playerBox.max.x;
    float dy1 = otherBox.max.y - playerBox.min.y;
    float dy2 = otherBox.min.y - playerBox.max.y;
    float dz1 = otherBox.max.z - playerBox.min.z;
    float dz2 = otherBox.min.z - playerBox.max.z;

    // Set dx to whichever of dx1/dx2 have a lower abs
    float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;
    // Ditto for dy
    float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;
    // Ditto for dz
    float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

    // Whichever is closest, adjust x/y position
    if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <= Maths::abs(dz))
    {
        pos.x += dx;
    }
    else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <= Maths::abs(dz))
    {
        pos.y += dy;
    }
    else
    {
        pos.z += dz;
    }
}

void FPSActor::updateActor(float dt)
{
    Actor::updateActor(dt);

    if (!Maths::nearZero(moveComponent->getAngularSpeed()))
    {
        Quaternion rotation = getRotation();
        float angle = moveComponent->getAngularSpeed() * dt;  // Calcul de l'angle en fonction du deltaTime
        Quaternion incrementalRotation(Vector3::unitY, angle);  // Rotation autour de l'axe Y (vertical)
        rotation = Quaternion::concatenate(rotation, incrementalRotation);
        setRotation(rotation);
    }

    // Play the footstep if we're moving and haven't recently
    lastFootstep -= dt;
    if (!Maths::nearZero(moveComponent->getForwardSpeed()) && lastFootstep <= 0.0f)
    {
        lastFootstep = 0.5f;
    }

    // Update position and rotation of the FPS model relatively to the player position
    Vector3 modelPosition = getPosition();
    modelPosition += getForward() * MODEL_OFFSET.x;
    modelPosition += getRight() * MODEL_OFFSET.y;
    modelPosition.z += MODEL_OFFSET.z;
    FPSModel->setPosition(modelPosition);
    Quaternion q = getRotation();
    q = Quaternion::concatenate(q, Quaternion(getRight(), cameraComponent->getPitch()));
    FPSModel->setRotation(q);

    fixCollisions();
}

void FPSActor::actorInput(const InputState& inputState)
{
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;

    // Forward and backward movement
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
    {
        forwardSpeed += 1000.0f;
    }
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
    {
        forwardSpeed -= 1000.0f;
    }

    // Rotation left and right
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
    {
        angularSpeed -= Maths::pi;
    }
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
    {
        angularSpeed += Maths::pi;
    }
    
    if (inputState.keyboard.getKeyValue(SDL_SCANCODE_E))  
    {
        cameraComponent->setPitch(0.0f);
    }

    moveComponent->setForwardSpeed(forwardSpeed);
    moveComponent->setAngularSpeed(angularSpeed);

    // Mouse movement for pitch and yaw
    Vector2 mousePosition = inputState.mouse.getPosition();
    float x = mousePosition.x;
    float y = mousePosition.y;
    const int maxMouseSpeed = 500;
    const float maxAngularSpeed = Maths::pi * 8;

    if (x != 0)
    {
        angularSpeed = x / maxMouseSpeed;
        angularSpeed *= maxAngularSpeed;
    }
    moveComponent->setAngularSpeed(angularSpeed);

    const float maxPitchSpeed = Maths::pi * 8;
    float pitchSpeed = 0.0f;
    if (y != 0)
    {
        pitchSpeed = y / maxMouseSpeed;
        pitchSpeed *= maxPitchSpeed;
    }
    cameraComponent->setPitchSpeed(pitchSpeed);

    // Update forward direction for flying movement
    Vector3 fullDirection = getForward();
    Quaternion pitchRotation(getRight(), cameraComponent->getPitch());
    fullDirection = Vector3::transform(fullDirection, pitchRotation);
    fullDirection.normalize();
    moveComponent->setForwardDirection(fullDirection);

    // Shoot
    if (inputState.mouse.getButtonState(1) == ButtonState::Pressed)
    {
        shoot();
    }
}

void FPSActor::shoot()
{
    Vector3 start = getPosition();
    Vector3 dir = cameraComponent->getForward(); 
    dir.normalize();

    BallActor* ball = new BallActor();
    ball->setPlayer(this);
    Vector3 offset(0.0f, 0.0f, -60.0f);
    ball->setPosition(start + offset);
    ball->rotateToNewForward(dir);


    ball->getMoveComponent()->setForwardDirection(dir);  
    ball->getMoveComponent()->setForwardSpeed(2000.0f);  
}

void FPSActor::setFootstepSurface(float value) {}

void FPSActor::setVisible(bool isVisible) {}

void FPSActor::setEnd(bool pendGame)
{
    endGame = pendGame;
}

void FPSActor::fixCollisions()
{
    computeWorldTransform();

    const AABB& playerBox = boxComponent->getWorldBox();
    Vector3 pos = getPosition();

    auto& planes = getGame().getPlanes();
    for (auto pa : planes)
    {
        const AABB& planeBox = pa->getBox()->getWorldBox();
        if(Collisions::intersect(playerBox, planeBox))
        {
            resolveCollision(playerBox, planeBox, pos);
        }
    }
    
    const auto& cubes = getGame().getCubes();
    for(const auto& cube : cubes)
    {
        const AABB& cubeBox = cube->getBox()->getWorldBox();
        if (Collisions::intersect(playerBox, cubeBox))
        {
            resolveCollision(playerBox, cubeBox, pos);
        }
    }

    const auto& doors = getGame().getDoors();
    for(const auto& door : doors)
    {
        const AABB& DoorBox = door->getBox()->getWorldBox();
        if (Collisions::intersect(playerBox, DoorBox))
        {
            resolveCollision(playerBox, DoorBox, pos);
        }
    }

    setPosition(pos);
    boxComponent->onUpdateWorldTransform();

    const auto& teleporter = getGame().getTPs();
    const AABB& TPBox = teleporter->getBox()->getWorldBox();
    if (Collisions::intersect(playerBox, TPBox))
    {
        std::cout << "Collision avec TP" << std::endl;
        setPosition(Vector3(0.0f, 1750.0f, 850.0f));
    }

    const auto& endGame = getGame().getEnd();
    const AABB& EndBox = endGame->getBox()->getWorldBox();
    if (Collisions::intersect(playerBox, EndBox))
    {
        setEnd(true);
    }
}

void FPSActor::setHP(int php)
{
    hp = php;
}

void FPSActor::damage()
{
    setHP(hp -= 1);
}