#pragma once
#include"charaBase.h"

class Enemy : public CharaBase
{
public:
	Enemy();
	~Enemy();

	void update()override;
	void draw()override;

	VECTOR Getposition_()const { return position_; }

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

	const int move_speed = 5;
};