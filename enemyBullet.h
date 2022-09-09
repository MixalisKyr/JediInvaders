#pragma once
#include "gameObject.h"
#include "config.h"
#include "enemy.h"

class EnemyBullet : public GameObject{
	float pos_x = 500.0f;
	float pos_y = 80.0f;
	float blast_speed = 1.1f;
	bool active = true;
public:
	void update() override;
	void draw() override;
	void init() override;
	EnemyBullet(const class Game& mygame);
	void setEnemyPosX(float x);
	Disk getCollisionHull() const;
	bool isActive() { return active; }
	~EnemyBullet();
	float  resetEnemyBullet() {
		pos_x = 500.0f;
		pos_y = 80.0f;
		return pos_x, pos_y; }

};