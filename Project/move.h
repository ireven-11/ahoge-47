#pragma once
#include"iState.h"
#include<memory>

class Player;

class MoveState : public IState
{
public:
	MoveState();
	~MoveState();

	void changeState(Player* player);
	void update(Player* player);

private:

};