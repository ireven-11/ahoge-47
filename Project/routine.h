#pragma once
#include<memory>
#include<list>
#include"player.h"

using namespace std;

class SceneManager;

class Routine
{
public:
	Routine();
	~Routine();

	void game();

	shared_ptr<SceneManager> sceneManager = make_shared<SceneManager>();
	shared_ptr<CharaBase> player = make_shared<Player>();
	list<shared_ptr<CharaBase>> enemy;

private:
	int backGraph_;
	int spawnCount_;
	int timer_;
	int spawnLevel_;

	const int max_spawn_count = 5;

	void gameRoop();
	void title();
	void play();
	void result();
	void spawnEnemy();
	void reset();
};