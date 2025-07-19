#pragma once

class Player;

class GarlicShot
{
public:
	GarlicShot(Player* player);
	~GarlicShot();

	void update();
	void reset(Player* player);

	VECTOR Getposition_()const { return position_; }

private:
	void draw();

	VECTOR	position_;
	bool	canExist_;
	int		mouseX_;
	int		mouseY_;
	VECTOR  moveVector_;
	double	rotationAngle_;
	int		graphHandle_ = LoadGraph("graph/043776-removebg-preview.png");
	
	const int shot_speed	= 10;
	const int widht			= 100;
	const int height		= 100;
};