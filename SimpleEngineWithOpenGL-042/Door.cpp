#include "Door.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"

Door::Door()
{
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = &Assets::getMesh("Mesh_Cube");
    mc->setMesh(*mesh);
    box = new BoxComponent(this);
    box->setObjectBox(mesh->getBox());

    getGame().addDoors(this);
}
Door::~Door()
{
    getGame().removeActor(this);
}

void Door::openDoor()
{
    if(isOpen == true)
    {
        setState(ActorState::Dead);
    }
}

void Door::setStateDoor(bool pisOpen)
{
    isOpen = pisOpen;
}

void Door::updateActor(float dt)
{
    openDoor();
}
