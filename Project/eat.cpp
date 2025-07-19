#include"DxLib.h"
#include"eat.h"
#include"player.h"

EatState::EatState()
{
}

EatState::~EatState()
{
}


void EatState::changeState(Player* player)
{
	player->checkHitKeyEat();
}

void EatState::update(Player* player)
{
	changeState(player);
	player->addGage();
}
