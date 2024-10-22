#include "KeyDoor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"
#include "FPSActor.h"

bool KeyDoor::isKeyOpen = false;

KeyDoor::KeyDoor()
{
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = &Assets::getMesh("Mesh_Door");
    mc->setMesh(*mesh);
    box = new BoxComponent(this);
    box->setObjectBox(mesh->getBox());
    getGame().addKeyDoors(this);
}
KeyDoor::~KeyDoor()
{
    getGame().removeActor(this);
}

void KeyDoor::openKeyDoor()
{
    if (isKeyOpen == true)
    {
        setPosition(Vector3(0.0f, 0.0f, -650.0f));
    }
}

void KeyDoor::setStateKeyDoor(bool pisKeyOpen)
{
    isKeyOpen = pisKeyOpen;
}

void KeyDoor::updateActor(float dt)
{
    openKeyDoor();
}
