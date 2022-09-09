#include "enemyBullet.h"
#include "graphics.h"
#include "config.h"
#include "game.h"
#include "enemy.h"


void EnemyBullet::update()
{

	if (graphics::getKeyState(graphics::SCANCODE_P))
	{

		graphics::playSound(std::string(ASSET_PATH) + "mikro1.mp3", 0.01f, false);
		pos_y += blast_speed * graphics::getDeltaTime() / 1.0f;

	}
	if (pos_y >= ENEMY_BULLET_STRIKE || !graphics::getKeyState(graphics::SCANCODE_P)) {
			
		pos_y = 80;

	}

		

}

void EnemyBullet::draw()
{
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "red_laser.png";
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.0f;
	graphics::drawRect(pos_x, pos_y, 25, 25, br);
	br.texture = "";
	graphics::setOrientation(0.0f);

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

void EnemyBullet::init()
{
}

EnemyBullet::EnemyBullet(const Game& mygame)
	: GameObject(mygame)
{
}

void EnemyBullet::setEnemyPosX(float x)
{
	this->pos_x = x;
}

Disk EnemyBullet::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 15.0f;
	return disk;
}

EnemyBullet::~EnemyBullet()
{
}
