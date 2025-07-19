#include"DxLib.h"
#include"move.h"
#include"player.h"

MoveState::MoveState()
{
}

MoveState::~MoveState()
{
}

void MoveState::changeState(Player* player)
{
	player->checkHitKeyEat();
}

void MoveState::update(Player* player)
{
	changeState(player);
	player->checkHitKeyMove();
	player->throwGarlic();
}