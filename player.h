#pragma once
#include "gameObject.h"
#include "config.h"
#include "bullet.h"

class Player : public GameObject, public Collidable
{
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT / 2 + 200;
	float speed = 20.0f;
	float life = 1.0f;
public:
	 Player(const class Game& mygame);
	 void update() override;
	 void draw() override;
	 void init() override;
	 float getPosX() { return pos_x; }
	 Disk getCollisionHull() const override;
	 float getRemainingLife() const { return life; }
	 void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
	 float resetPlayerLife() {
		 life = 1.0f;
		 return life;
	 }
	 float resetPlayerPos() { 
		 pos_x = CANVAS_WIDTH / 2;
		 pos_y = CANVAS_HEIGHT / 2 + 200;
		 return pos_x, pos_y; }
	 
};