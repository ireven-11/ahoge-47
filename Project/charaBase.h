#pragma once


class CharaBase
{
public:
	CharaBase();
	~CharaBase();

	virtual void update();
	virtual void draw();
	virtual void reset();

	virtual VECTOR Getposition_()const = 0;

private:
};