#pragma once

class Player;

class IState
{
public:
	virtual ~IState() = default;

	virtual void changeState(Player* player) = 0;
	virtual void update(Player* player) = 0;

private:

};