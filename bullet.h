#pragma once
#include "gameObject.h"
#include "config.h"
#include "player.h"


class Bullet : public GameObject {
	float pos_x = 500.0f;
	float pos_y = 400.0f;
	float blast_speed = 1.1f;
	bool active = true;

	
public:
	void update() override;
	void draw() override;
	void init() override;
	Bullet(const class Game& mygame);
	Disk getCollisionHull() const;
	bool isActive() { return active; }
	void setPosX(float x);
	float resetBullet() {
		pos_x = CANVAS_WIDTH/2;
		pos_y = 400.0f;
		return pos_x, pos_y; }
	~Bullet();
	
	
};