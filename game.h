#pragma once
#include "player.h"
#include "enemy.h"
#include "bar.h"
#include "bullet.h"
#include "enemyBullet.h"

class Game {
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_END} status_t;
	Player* player = nullptr;
	bool player_initialized = false;

	Enemy* enemy = nullptr;
	bool enemy_initialized = false;

	bool checkCollision1();
	bool checkCollision2();
	bool checkCollision3();
	bool checkCollision4();
	bool debug_mode = false;



	status_t status = STATUS_START;

	Bar* bar = nullptr;
	bool bar_initialized = false;

	Bullet* bullet = nullptr;
	bool bullet_initialized = false;

	void spawnBullet();
	void checkBullet();

	EnemyBullet* enemy_bullet = nullptr;
	bool enemy_bullet_initialized = false;

	

	void spawnEnemyBullet();
	void checkEnemyBullet();

	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	void resetScore() { player_score = 0, enemy_score = 0; }
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();

	void spawnbar();

	bool player_win = false;
	int player_score = 0;
	int enemy_score = 0;


public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	void init();
	Game();
	~Game();



};