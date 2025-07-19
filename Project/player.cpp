#include"DxLib.h"
#include"player.h"
#include"garlicShot.h"

Player::Player()
{
	LoadDivGraph("graph/Boy_Sheet.png",graph_max_number,graph_x_number,graph_y_number, graph_size, graph_size,graphHandle_);
	graphGarlic_ = LoadGraph("graph/043776-removebg-preview.png");
	siteGraph_	= LoadGraph("graph/26695953.png");
	reset();
}

Player::~Player()
{
	DeleteGraph(*graphHandle_);
	DeleteGraph(graphGarlic_);
	DeleteGraph(siteGraph_);
}

void Player::reset()
{
	state_			= moveState_();
	position_		= VGet(init_position.x, init_position.y, init_position.z);
	animationCount_ = animation_run_minimum_range;
	waitCount_		= 0;
	isFacingRight_	= false;
	gage_			= 0;
	gageLevel_		= 0;
	throwCount_		= 0;
}

void Player::update()
{
	state_->update(this);
	pushBack();

	for (auto it = garlicShot_.begin(); it != garlicShot_.end(); )
	{
		(*it)->update();

		auto pos = (*it)->Getposition_();
		if (pos.x > 1920 || pos.x < 0 || pos.y > 1080 || pos.y < 0)
		{
			it = garlicShot_.erase(it);  // erase は次のイテレータを返す
		}
		else
		{
			++it;
		}
	}

	draw();
}

void Player::draw()
{
	if (state_ == eatState_())
	{
		if (!isFacingRight_)
		{
			DrawExtendGraph(position_.x, position_.y, position_.x + graph_width, position_.y + graph_height, graphHandle_[animation_eat], TRUE);
			DrawExtendGraph(position_.x + garlic_shift_number, position_.y + garlic_shift_number * 2,
				position_.x + garlic_shift_number + garlic_width, position_.y + garlic_shift_number * 2 + garlic_height, graphGarlic_, TRUE);
		}
		else
		{
			DrawExtendGraph(position_.x + graph_width, position_.y, position_.x, position_.y + graph_height, graphHandle_[animation_eat], TRUE);
			DrawExtendGraph(position_.x + graph_width - garlic_shift_number, position_.y + garlic_shift_number * 2,
				position_.x + graph_width - garlic_shift_number - garlic_width, position_.y + garlic_shift_number * 2 + garlic_height, graphGarlic_, TRUE);
		}
	}
	else
	{
		waitCount_++;
		if (waitCount_ == count_up_time)
		{
			animationCount_++;
			waitCount_ = 0;
		}
		if (animationCount_ > animation_run_max_range)
		{
			animationCount_ = animation_run_minimum_range;
		}
		if (!isFacingRight_)
		{
			DrawExtendGraph(position_.x, position_.y, position_.x + graph_width, position_.y + graph_height, graphHandle_[animationCount_], TRUE);
		}
		else
		{
			DrawExtendGraph(position_.x + graph_width, position_.y, position_.x, position_.y + graph_height, graphHandle_[animationCount_], TRUE);
		}
	}

	GetMousePoint(&mouseX_, &mouseY_);
	DrawExtendGraph(mouseX_ - graph_width / 2, mouseY_ - graph_height /2, mouseX_ + graph_width / 2, mouseY_ + graph_height / 2, siteGraph_, TRUE);

	DrawBox(position_.x, position_.y, position_.x + graph_width, position_.y + graph_height, GetColor(255, 0, 0), FALSE);
}

void Player::checkHitKeyMove()
{
	if (CheckHitKey(KEY_INPUT_RIGHT) == true || CheckHitKey(KEY_INPUT_D) == true)
	{
		position_.x += move_speed;
		isFacingRight_ = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) == true || CheckHitKey(KEY_INPUT_A) == true)
	{
		position_.x -= move_speed;
		isFacingRight_ = false;
	}
}

void Player::checkHitKeyEat()
{
	if (CheckHitKey(KEY_INPUT_SPACE) == true)
	{
		state_ = eatState_();
	}
	else
	{
		state_ = moveState_();
	}
}

void Player::pushBack()
{
	if (position_.x + graph_width > 1920)
	{
		position_.x = 1920 - graph_width;
	}
	else if (position_.x < 0)
	{
		position_.x = 0;
	}
}

void Player::addGage()
{
	gage_++;

	if (gage_max_number > gage_)
	{
		gage_ = 0;
		gageLevel_++;
	}
}

void Player::throwGarlic()
{
	throwCount_++;
	if (throwCount_==throw_count_max_number)
	{
		garlicShot_.emplace_back(make_shared<GarlicShot>(this));
		throwCount_ = 0;
	}
}