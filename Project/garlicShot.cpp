#include"DxLib.h"
#include"garlicShot.h"
#include"player.h"

GarlicShot::GarlicShot(Player* player)
{
	reset(player);
}

GarlicShot::~GarlicShot()
{
}

void GarlicShot::reset(Player* player)
{
	position_		= VGet(player->Getposition_().x, player->Getposition_().y, 0);
	canExist_		= true;
	moveVector_		= VGet(shot_speed * player->GetgageLevel_(), 0, 0);
	GetMousePoint(&mouseX_, &mouseY_);
	moveVector_ = VGet((mouseX_ - position_.x) / 50, (mouseY_ - position_.y) / 50, 0);
}

void GarlicShot::update()
{
	if (canExist_)
	{
		position_ = VAdd(position_, moveVector_);
		draw();
	}
}

void GarlicShot::draw()
{
	DrawExtendGraph(position_.x, position_.y, position_.x + widht, position_.y + height, graphHandle_, TRUE);

	DrawBox(position_.x, position_.y, position_.x + widht, position_.y + height, GetColor(255, 0, 0), FALSE);
}

void GarlicShot::dieShot()
{
	canExist_ = false;
}