#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"
#include "HUD.h"

using std::vector;

enum class GameState
{
	Gameplay, Pause, Quit
};

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : state(GameState::Gameplay), isUpdatingActors(false), fps(nullptr), crosshair(nullptr) {}

public:
	bool initialize();
	std::vector<std::vector<int>> loadLevel(const std::string& filename);
	void load();
	void loop();
	void unload();
	void close();

	GameState getState() const { return state; }
	void setState(GameState stateP);

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }
	InputSystem& getInputSystem() { return inputSystem; }
	const vector<class UIScreen*>& getUIStack() { return UIStack; }
	void pushUI(class UIScreen* screen);
	HUD* getHUD() { return hud; }

	// Game-specific
	void addPlane(class PlaneActor* plane);
	void removePlane(class PlaneActor* plane);
	vector<PlaneActor*>& getPlanes() { return planes; }
	class FPSActor* getPlayer() { return fps; }

private:
	void processInput();
	void update(float dt);
	void render();

	GameState state;
	Window window;
	RendererOGL renderer;

	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	vector<class UIScreen*> UIStack;
	HUD* hud;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game specific

	class FPSActor* fps;
	class SpriteComponent* crosshair;
	vector<PlaneActor*> planes;
};

