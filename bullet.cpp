#include "bullet.h"
#include "graphics.h"
#include "game.h"
#include "config.h"
#include "util.h"


void Bullet::update()
{
	
	
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		
		
		pos_y -= blast_speed * graphics::getDeltaTime() / 1.0f;
	    graphics::playSound(std::string(ASSET_PATH) + "mikro1.mp3", 0.01f, false);	
	}
	
	if (pos_y <= BULLET_STRIKE || !graphics::getKeyState(graphics::SCANCODE_SPACE)) {
		pos_y = 400;
	}
}


void Bullet::draw()
{

	graphics::Brush br;
	graphics::setOrientation(90.0f);
	br.texture = std::string(ASSET_PATH) + "green_laser.png";
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


void Bullet::init()
{	
}

Bullet::Bullet(const Game& mygame)
	: GameObject(mygame)
{
}
Bullet::~Bullet()
{
}

Disk Bullet::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 15.0f;
	return disk;
}

void Bullet::setPosX(float x)
{
	this->pos_x = x;
}