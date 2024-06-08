#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD();
	~HUD();

	void update(float dt) override;
	void updateHP(float dt);
	void updateCondition(float dt);
	void draw(class Shader& shader) override;

	void addTargetComponent(class TargetComponent* tc);
	void removeTargetComponent(class TargetComponent* tc);


protected:
	void updateCrosshair(float deltaTime);
	void updateRadar(float deltaTime);

	class Texture* crosshair;
	class Texture* crosshairEnemy;
	class Texture* radar;
	class Texture* blipTex;
	class Texture* radarArrow;

	class Texture* healthBar;
	class Texture* healthBar1;
	class Texture* healthBar2;
	class Texture* healthBar3;
	
	class Texture* Empty;
	class Texture* GameOver;
	class Texture* Finished;
	

	std::vector<class TargetComponent*> targetComponents;
	bool isTargetingEnemy;
	bool isDead = false;
	vector<Vector2> blips;
	float radarRange;
	float radarRadius;
};
