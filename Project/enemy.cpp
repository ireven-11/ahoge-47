#include"DxLib.h"
#include"player.h"
#include"enemy.h"

Enemy::Enemy()
{
	reset();
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	move();
	draw();
}

void Enemy::draw()
{
	DrawExtendGraph(position_.x, position_.y, position_.x + graph_widht, position_.y + graph_height, graphHandle_, TRUE);

	DrawBox(position_.x, position_.y, position_.x + graph_widht, position_.y + graph_height, GetColor(255,0,0),FALSE);
}

void Enemy::reset()
{
	animationCount_ = 0;
	canExist_		= true;
	position_ = VGet(GetRand(1800) + 25, -100, 0);
	if(position_.x < 1000)
	{
		isRight_ = false;
	}
	else
	{
		isRight_ = true;
	}
}

void Enemy::move()
{
	if (position_.y < 800)
	{
		position_.y += move_speed;
	}
	else
	{
		if (isRight_)
		{
			position_.x -= move_speed;
		}
		else
		{
			position_.x += move_speed;
		}
	}
}