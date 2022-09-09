#include "game.h"
#include "graphics.h"
#include "config.h"


void Game::spawnBullet()
{
	if (!bullet) {
		bullet = new Bullet(*this);
	}
}

void Game::checkBullet()
{
	if (bullet && !bullet->isActive())
	{
		delete bullet;
		bullet = nullptr;
	}
}

void Game::spawnEnemyBullet()		//Dimiourgia antikeimenou typou enemy bullet
{
	if (!enemy_bullet)
	{
		enemy_bullet = new EnemyBullet(*this);
	}
}

void Game::checkEnemyBullet()
{
	if (enemy_bullet && !enemy_bullet->isActive())			// Elegxos an yparxei enemy_bullet kai diagrafi
	{
		delete enemy_bullet;
		enemy_bullet = nullptr;
	}
}

void Game::updateStartScreen()			// Update gia tin arxiki othoni
{




	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
	}
	
	
	
}

void Game::updateLevelScreen()
{
	//if (startgame)
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;


	}

	if (player)
		player->update();


	if (!enemy_initialized && graphics::getGlobalTime() > 1000)
	{
		enemy = new Enemy(*this);
		enemy_initialized = true;
	}

	if (enemy)
		enemy->update();

	if (!bullet_initialized && graphics::getGlobalTime() > 1000)
	{
		bullet = new Bullet(*this);
		bullet_initialized = true;

	}
	if(bullet)
		bullet->setPosX(player->getPosX());

	if (bullet)
		bullet->update();
	

	checkBullet();
	spawnBullet();

	if (!enemy_bullet_initialized && graphics::getGlobalTime() > 1000)
	{
		enemy_bullet = new EnemyBullet(*this);
		enemy_bullet_initialized = true;
	}
	if (enemy_bullet)
		enemy_bullet->setEnemyPosX(enemy->getEnPosX());
	if (enemy_bullet)
		enemy_bullet->update();


	checkEnemyBullet();
	spawnEnemyBullet();

	spawnbar();

	if (bar)
		bar->update();

	if (checkCollision1() || checkCollision3())
	{
		delete enemy_bullet;
		enemy_bullet = nullptr;

		
	}


	if (checkCollision2() || checkCollision4())
	{

		delete bullet;
		bullet = nullptr;

		
	}

	if (player->getRemainingLife() == 0.0f){				   //Elegxos an i zwi tou player1 einai 0 

		status = STATUS_END;
		
		player->resetPlayerLife();							   //Reset wste i othoni na einai etoimi gia new game
		enemy->resetEnemyLife();							   //Reset wste i othoni na einai etoimi gia new game
		enemy->resetEnemyPos();								   //Reset wste i othoni na einai etoimi gia new game
		player->resetPlayerPos();							   //Reset wste i othoni na einai etoimi gia new game
		bullet->resetBullet();								   //Reset wste i othoni na einai etoimi gia new game
		player_win = false;									   //Reset wste i othoni na einai etoimi gia new game
		graphics::stopMusic();
		graphics::playMusic(std::string(ASSET_PATH) + "crew.mp3", 0.4f, false, 2000);
		enemy_score++;
	}
	else if (enemy->getEnemyRemainingLife() == 0.0f){		   //Elegxos an i zwi toy enemy(player2) einai 0
		status = STATUS_END;
		player_win = true;
		player->resetPlayerLife();							   //Reset wste i othoni na einai etoimi gia new game
		enemy->resetEnemyLife();							   //Reset wste i othoni na einai etoimi gia new game
		enemy_bullet->resetEnemyBullet();					   //Reset wste i othoni na einai etoimi gia new game
		enemy->resetEnemyPos();								   //Reset wste i othoni na einai etoimi gia new game
		player->resetPlayerPos();							   //Reset wste i othoni na einai etoimi gia new game
		graphics::stopMusic();
		graphics::playMusic(std::string(ASSET_PATH) + "force.mp3", 0.4f, false, 2000);
		player_score++;
		
	}
	
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_Q))
	{
		status = STATUS_START;
		graphics::stopMusic();
		graphics::playMusic(std::string(ASSET_PATH) + "jedi.mp3", 0.9f, true, 4000);

	}
}

void Game::drawStartScreen()
{
	
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg.png";
	br.outline_opacity = 0.0f;
	float offset = CANVAS_WIDTH / 2 * sinf(graphics::getGlobalTime() / 1000.0f) / 20;

	graphics::drawRect(CANVAS_WIDTH / 2 + offset, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.texture = std::string(ASSET_PATH) + "falcon_3.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(150, 320, 70, 85, br);

	br.texture = std::string(ASSET_PATH) + "tie.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(850, 320, 70, 85, br);

	char info[40];
	sprintf_s(info, "Press ENTER to start");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT / 2, 30, info, br);

	char info2[40];
	sprintf_s(info2, "Press ESC to exit");
	graphics::drawText(CANVAS_WIDTH / 2 - 100, CANVAS_HEIGHT / 2 + 30, 15, info2, br);
	
	//Player1 infos
	char p[40];
	sprintf_s(p, "Player1  Buttons");
	graphics::drawText(30, 400, 20, p, br);

	char l[40];
	sprintf_s(l , "- Arrow keys to move");
	graphics::drawText(30, 420, 10, l , br); 

	char a[40];
	sprintf_s(a, "- Hold  SPACE to shoot");
	graphics::drawText(30, 440, 10, a, br);

	//Player2 infos
	char y[40];
	sprintf_s(y, "Player2  Buttons");
	graphics::drawText(750, 400, 20, y, br);

	char e[100];
	sprintf_s(e, "- A(left)  D(right) keys to move");
	graphics::drawText(750, 420, 10, e, br);

	char r[40];
	sprintf_s(r, "- Hold  P to shoot");
	graphics::drawText(750, 440, 10, r, br);

	//up logo
	char logo[400];
	sprintf_s(logo, "Jedi invaders");
	graphics::drawText(350, 40, 40, logo, br);
	
}



void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg.png";
	br.outline_opacity = 0.0f;
	float offset = CANVAS_WIDTH / 2 * sinf(graphics::getGlobalTime() / 1000.0f) / 20;

	graphics::drawRect(CANVAS_WIDTH / 2 + offset, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	
	if (player)									//draw player
		player->draw();							//draw player
											
	if (enemy)									//draw enemy
		enemy->draw();							//draw enemy
												
	if (bar)									//draw bar
		bar->draw();							//draw bar
											
	if (bullet)									//draw bullet
		bullet->draw();							//draw bullet
												
	if (enemy_bullet)							//draw enemy_bullet
		enemy_bullet->draw();					//draw enemy_bullet

	
	//DRAW UI/INTERFACE
	char info[40];
	sprintf_s(info, "P1 Life");
	graphics::drawText(163, 457, 20, info, br);

	char f[40];
	sprintf_s(f, "P2 Life");
	graphics::drawText(750, 37, 20, f, br);

	float player_life = player ? player->getRemainingLife() : 0.0f;

	br.outline_opacity = 1.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2 - 400 - ((1.0f - player_life) * 120 / 2), CANVAS_HEIGHT / 2 + 200, player_life *120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;


	float enemy_life = enemy ? enemy->getEnemyRemainingLife() : 0.0f;

	br.outline_opacity = 1.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - enemy_life) + enemy_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2 * (1.0f - enemy_life) + enemy_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;

	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - enemy_life) * 120 / 2), 30, enemy_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	

}

void Game::drawEndScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg.png";
	br.outline_opacity = 0.0f;
	float offset = CANVAS_WIDTH / 2 * sinf(graphics::getGlobalTime() / 1000.0f) / 20;

	graphics::drawRect(CANVAS_WIDTH / 2 + offset, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	char menu[400];
	sprintf_s(menu, "Press  q  to  go  to  menu");
	graphics::drawText(300, 450, 30, menu, br);

	if (player_win == true)				//elegxos gia to poios nikise kai emfanisi katallilou minimatos
	{
			char en[40];
			sprintf_s(en, "	The  Rebels  won!");
			graphics::drawText(CANVAS_WIDTH / 2 - 140, CANVAS_HEIGHT / 2, 30, en, br);
			char p1[400];
			sprintf_s(p1, "May the force be with you!");
			graphics::drawText(CANVAS_WIDTH / 2 - 220, CANVAS_HEIGHT / 2 + 40, 30, p1, br);
	}else{

		char pl[40];
		sprintf_s(pl, "	The  Empire  Won!");
		graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT / 2, 30, pl, br);
		char p2[400];
		sprintf_s(p2, "Long  Live  the  Empire!");
		graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT / 2 + 40, 30, p2, br);
		
	}
	char menu5[400];
	sprintf_s(menu5, "Player 1 score : %d",player_score);
	graphics::drawText(50, 70, 15, menu5, br);
	char menu6[400];
	sprintf_s(menu6, "Player 2 score : %d",enemy_score);
	graphics::drawText(750, 70, 15, menu6, br);
	
}


void Game::spawnbar()
{
	if (!bar)						//dimiourgia antikeimenou bar
	{
		bar = new Bar(*this);
	}
}

bool Game::checkCollision1()				//Elegxos gia an tha kanei collision o player me tin sfaira tou enemy(enemy_bullet)
{
	if (!enemy_bullet || !player)
	{
		return false;
	}

	Disk d1 = player->getCollisionHull();
	Disk d2 = enemy_bullet->getCollisionHull();

	float Edx = d1.cx - d2.cx;
	float Edy = d1.cy - d2.cy;

	if (sqrt(Edx * Edx + Edy * Edy) < d1.radius + d2.radius)
	{
		player->drainLife(0.1f);
		return true;
	}
	else
		return false;
}

bool Game::checkCollision2()				//Elegxos an tha kanei collision i sfaira tou player me ton enemy
{
	if (!bullet || !enemy)
	{
		return false;
	}

	Disk d3 = enemy->getCollisionHull();
	Disk d4 = bullet->getCollisionHull();

	float dx = d3.cx - d4.cx;
	float dy = d3.cy - d4.cy;
						
	if (sqrt(dx * dx + dy * dy) < d4.radius + d3.radius)
	{
		enemy->drainEnemyLife(0.1f);				//afairesi zwis apo ton enemy an tha ton petyxei o player
		return true;
	}
	else
		return false;
}

bool Game::checkCollision3()						//elegxos an tha kanei collision i sfaira tou enemy me tin mpara
{
	if (!enemy_bullet || !bar)
	{
		return false;
	}

	Disk d5 = bar->getCollisionHull();
	Disk d6 = enemy_bullet->getCollisionHull();

	float Edx = d5.cx - d6.cx;
	float Edy = d5.cy - d6.cy;

	if (sqrt(Edx * Edx + Edy * Edy) < d5.radius + d6.radius)
	{
		return true;
	}
	else
		return false;
}

bool Game::checkCollision4()				//elegxos an tha kanei collision i sfaira tou player me tin mpara
{
	if (!bullet || !bar)
	{
		return false;
	}

	Disk d7 = bar->getCollisionHull();
	Disk d8 = bullet->getCollisionHull();

	float dx = d7.cx - d8.cx;
	float dy = d7.cy - d8.cy;

	if (sqrt(dx * dx + dy * dy) < d7.radius + d8.radius)
	{
		return true;
	}
	else
		return false;
}
void Game::update()				//klisi tis katallilis update function
{
	if (status == STATUS_START)
	{
		updateStartScreen();

	}
	if (status == STATUS_PLAYING)
	{
		updateLevelScreen();
	}
	if (status == STATUS_END)
	{
		updateEndScreen();
	}
}

void Game::draw()			// klisi tis katallilis draw function
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	if(status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	if(status == STATUS_END)
	{
		drawEndScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "galaxy.ttf");
	if (status == STATUS_START)
	{
		graphics::playMusic(std::string(ASSET_PATH) + "jedi.mp3", 0.9f, true, 4000);
		
	}
	

	
}

Game::Game()
{

}

Game::~Game()
{
	if (player) {
		delete (player);
	}
	if (enemy) {
		delete (enemy);
	}

}
