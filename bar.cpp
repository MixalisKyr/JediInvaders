#include "bar.h"
#include "graphics.h"
#include "config.h"
#include "game.h"

int sign = -1;

void Bar::update()
{
	if (pos_x <= BAR_END) {
		sign = sign * (-1);
		pos_x = BAR_END;
	}
	if (pos_x >= BAR_START) {
		sign = sign * (-1);
		pos_x = BAR_START;
	}

	pos_x -= sign * speed * graphics::getDeltaTime() / 4.0f;

}

void Bar::draw()
{
	graphics::Brush br;
	
	
	br.texture = std::string(ASSET_PATH) + "lightsaber.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, CANVAS_HEIGHT/2, 130, 70, br);

	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = true;
		Disk hul = getCollisionHull();
		graphics::drawRect(hul.cx, hul.cy, 120, hul.radius, br);
	}
}

void Bar::init()
{

}

Disk Bar::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y + 100;
	disk.radius = 35.0f;
	return disk;
}

Bar::Bar(const Game& mygame)
	: GameObject(mygame)
{
}

Bar::~Bar() {}

