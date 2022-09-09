#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include "gameObject.h"
#include "game.h"
#include "util.h"

Enemy::Enemy(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

void Enemy::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime() / 100.f;
		
	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 100.f;

	}

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void Enemy::draw()
{
	graphics::Brush br;
	graphics::setOrientation(180.0f);
	br.texture = std::string(ASSET_PATH) + "tie.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 70, 85, br);
	graphics::setOrientation(0.0f);

	br.texture = "";

	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}

}

void Enemy::init()
{
	
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 38.0f;
	return disk;
}

