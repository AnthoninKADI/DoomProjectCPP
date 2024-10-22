#pragma once
#include "Actor.h"
#include "BoxComponent.h"

class Key : public Actor
{
public:
    Key();
    ~Key();
    class BoxComponent* getBox() { return box; }

private:
    class BoxComponent* box;
};
