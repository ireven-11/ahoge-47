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

	shared_ptr<CharaBase> player = make_shared<Player>();
	list<shared_ptr<CharaBase>> enemy;

private:
	int backGraph_;
	int spawnCount_;

	const int max_spawn_count = 100;

	void gameRoop(shared_ptr<SceneManager> sceneManager);
	void title();
	void play();
	void result();
	void spawnEnemy();
	void reset();
};