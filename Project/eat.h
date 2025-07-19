#pragma once
#include"iState.h"

class Player;

class EatState : public IState
{
public:
	EatState();
	~EatState();

	void changeState(Player* player);
	void update(Player* player);

private:

};