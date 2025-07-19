#pragma once
#include"charaBase.h"
#include<memory>
#include"iState.h"
#include"eat.h"
#include"move.h"
#include<list>

const int graph_width = 200;
const int graph_height = 200;

using namespace std;

class GarlicShot;

class Player : public CharaBase
{
public:
	Player();
	~Player();

	void update()override;
	void draw()override;
	void checkHitKeyMove();
	void checkHitKeyEat();
	void addGage();
	void throwGarlic();

	VECTOR Getposition_()const { return position_; }

private:
	void reset()override;
	void pushBack();
	
	int		graphHandle_[48];
	VECTOR	position_;
	int		animationCount_;
	int		waitCount_;
	bool	isFacingRight_;
	int		graphGarlic_;
	int		gage_;
	int		gageLevel_;
	list<shared_ptr<GarlicShot>> garlicShot_;
	int		throwCount_;
	int		mouseX_;
	int		mouseY_;
	int		siteGraph_;

	const int graph_max_number	= 48;
	const int graph_x_number	= 8;
	const int graph_y_number	= 6;
	const int graph_size		= 46;
	const VECTOR init_position	= VGet(1000, 800, 0);
	const int animation_run_minimum_range = 24;
	const int animation_run_max_range = 28;
	const int animation_eat		= 33;
	const int count_up_time		= 10;
	const int move_speed		= 5;
	const int garlic_div_number = 3;
	const int garlic_width		= 50;
	const int garlic_height		= 50;
	const int garlic_shift_number = 45;
	const int gage_max_number	= 200;
	const int throw_count_max_number = 40;
	
	//èÛë‘
	shared_ptr<IState> state_;
	static shared_ptr<EatState> eatState_()
	{
		static shared_ptr<EatState> state = make_shared<EatState>();
		return state;
	}
	static shared_ptr<MoveState> moveState_()
	{
		static shared_ptr<MoveState> state = make_shared<MoveState>();
		return state;
	}
};