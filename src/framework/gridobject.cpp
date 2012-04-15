#include "framework/gridobject.h"

bool GridObject::tweenTo(float target_x, float target_y, float target_z, float delta)
{
	if(target_x == x && target_y == y && target_z == z) return false;

	if(gridMovSpeed == 0)
	{
		this->x = target_x;
		this->y = target_y;
		this->z = target_z;
	}
	else if(delta != 0)
	{
		// should z have a different shift speed ?

		Vec2f normal;
		normal.x = target_x - this->x;
		normal.y = target_y - this->y;
		normal.normalize();

		float tmpx = this->x + normal.x * gridMovSpeed * delta;
		float tmpy = this->y + normal.y * gridMovSpeed * delta;

		if((normal.x < 0 && tmpx < target_x) 
			|| (normal.x > 0 && tmpx > target_x))
		{
			tmpx = target_x;
		}

		if((normal.y < 0 && tmpy < target_y) 
			|| (normal.y > 0 && tmpy > target_y))
		{
			tmpy = target_y;
		}

		this->x = tmpx;
		this->y = tmpy;
		this->z = target_z;
	}
	return true;
}