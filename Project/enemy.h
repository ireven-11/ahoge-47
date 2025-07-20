#pragma once
#include"charaBase.h"

class Enemy : public CharaBase
{
public:
	Enemy();
	~Enemy();

	void update()override;
	void draw()override;
	void die();

	VECTOR	Getposition_()const { return position_; }
	bool	GetcanExist_()const { return canExist_; }
	int		GetgageLevel_()const { return 0; }

private:
	void reset()override;
	void move();
	
	VECTOR	position_;
	bool	canExist_;
	int		animationCount_;
	int		graphHandle_ = LoadGraph("graph/copy.png");
	int		graph_widht	= 200;
	int		graph_height = 200;
	bool	isRight_;

	const int move_speed = 10;
};