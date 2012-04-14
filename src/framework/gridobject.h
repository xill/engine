#ifndef GRID_OBJ_H
#define GRID_OBJ_H

#include "camera/follow_point.hpp"

enum OBJTYPE 
{
	PROJECTILE = 0,
	OBJECT = 1
};


class GridObject : public FollowPoint
{
private:
	float x,y,z;
	int gridx,gridy;
	int x_off,y_off;
	int gridrange;
	int id;
	OBJTYPE type;

public:
	GridObject(OBJTYPE t = OBJECT) : x(10),y(10),z(0),gridx(0),gridy(0),x_off(0),y_off(0),gridrange(3),type(t),id(-1) {}

	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setZ(float z) { this->z = z; }
	void setGridX(int x) { this->gridx = x; }
	void setGridY(int y) { this->gridy = y; }
	void setGridRange(int range) { this->gridrange = range; } // needed?
	void setType(OBJTYPE type) { this->type = type; }
	void setId(int id) { this->id = id; }
	void setDesiredGridOffset(int x = 0, int y = 0) { this->x_off = x; this->y_off = y; }
	void setXOffset(int x) { this->x_off = x; }
	void setYOffset(int y) { this->y_off = y; }

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	int getGridX() { return gridx; }
	int getGridY() { return gridy; }
	int getXOffset() { return x_off; }
	int getYOffset() { return y_off; }
	int getGridRange() { return gridrange; }
	OBJTYPE getType() { return type; }
	int getId() { return id; }

};

#endif // GRID_OBJ_H
