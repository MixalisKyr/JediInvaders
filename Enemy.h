#pragma once
#include "gameObject.h"

class Enemy : public GameObject, public Collidable
{
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT / 2 - 200;
	float speed = 20.0f;
	bool active = true;
	float enemy_life = 1.0f;

public:
	Enemy(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getEnPosX() { return pos_x; }
	Disk getCollisionHull() const override;
	float getEnemyRemainingLife() const { return enemy_life; }
	void drainEnemyLife(float amount) { enemy_life = std::max<float>(0.0f, enemy_life - amount); }
	float resetEnemyLife(){
		enemy_life = 1.0f;
		return enemy_life;
	}
	float resetEnemyPos() {
		pos_x = CANVAS_WIDTH / 2;
		pos_y = CANVAS_HEIGHT / 2 - 200;
		return pos_x, pos_y; }
};