#include "player.h"
#include "graphics.h"
#include "config.h"
#include "game.h"
#include "util.h"
#include "gameObject.h"

Player::Player(const Game& mygame)
	: GameObject(mygame)
{
	init();
}

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -= speed * graphics::getDeltaTime() / 100.f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 100.f;
	}

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
}

void Player::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "falcon_3.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 70, 85, br);
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

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 40.0f;
	return disk;
}
