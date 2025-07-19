#pragma once

const int widht = 100;
const int height = 100;

class Player;

class GarlicShot
{
public:
	GarlicShot(Player* player);
	~GarlicShot();

	void update();
	void reset(Player* player);
	void dieShot();

	VECTOR	Getposition_()const { return position_; }
	bool	GetcanExist_()const { return canExist_; }

private:
	void draw();

	VECTOR	position_;
	bool	canExist_;
	int		mouseX_;
	int		mouseY_;
	VECTOR  moveVector_;
	double	rotationAngle_;
	int		graphHandle_ = LoadGraph("graph/043776-removebg-preview.png");
	
	const int shot_speed	= 30;
};