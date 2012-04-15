#ifndef GRID_OBJ_H
#define GRID_OBJ_H

#include "camera/follow_point.hpp"
#include "math/vec2.hpp"

enum OBJTYPE 
{
	PROJECTILE = 0,
	OBJECT = 1
};


class GridObject : public FollowPoint
{
private:
	// actual location in 3d space.
	float x,y,z;

	// grid which owns this object.
	int gridx,gridy;

	// movement offset. this is grid relative not space.
	int x_off,y_off;

	// id key of this object.
	int id;

	// type of the object.
	OBJTYPE type;

	// if this object allows sharing of it's grid.
	bool sharesGrid;

	// speed this object transitions between grids. value 0 will make the movement directly snap to location.
	float gridMovSpeed;

	// currently unused.
	int gridrange;

public:
	GridObject(OBJTYPE t = OBJECT) 
	: x(10)
	, y(10)
	, z(0)
	, gridx(0)
	, gridy(0)
	, x_off(0)
	, y_off(0)
	, gridMovSpeed(0.7f)
	, gridrange(3)
	, type(t)
	, id(-1)
	, sharesGrid(false)
	{}

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
	void setSharesGrid(bool status) { this->sharesGrid = status; }
	void setGridMovementSpeed(float speed) { this->gridMovSpeed = speed; }

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
	bool canShareGrid() { return sharesGrid; }
	float getGridMovementSpeed() { return gridMovSpeed; }
	
	// returns true if tweening was performed. false if not.
	bool tweenTo(float target_x, float target_y, float target_z, float delta);
};

#endif // GRID_OBJ_H
