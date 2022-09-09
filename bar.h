#pragma once
#include "gameObject.h"
#include "config.h"
#include "graphics.h"
#include "util.h"

class Bar : public GameObject {
	float pos_x = BAR_WIDTH, pos_y = BAR_HEIGHT/2;
	float speed = 1.0f;
	float x1 = 300.0f;
	float y1 = 100.0f;
	float x2 = 500.0f;
	float y2 = 150.0f;
	graphics::Brush brush;

public:
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const;
	Bar(const class Game& mygame);
	~Bar();

};