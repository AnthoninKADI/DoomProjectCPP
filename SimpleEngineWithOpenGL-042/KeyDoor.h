#pragma once
#include "Actor.h"
#include "BoxComponent.h"

class KeyDoor : public Actor
{
public:
    KeyDoor();
    ~KeyDoor();
    class BoxComponent* getBox() { return box; }
    void openKeyDoor();
    void setStateKeyDoor(bool pisKeyOpen);
    void updateActor(float dt) override;
    static bool isKeyOpen;


private:
    class BoxComponent* box;
    
};









