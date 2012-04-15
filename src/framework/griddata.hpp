#ifndef GRIDDATA_HPP
#define GRIDDATA_HPP

#include <vector>
#include "gridobject.h"

class GridData
{
public:
	// which ruleset is used in this grid.
	int ruleid;

	// z-axis elevation of this grid.
	float elevation;

	// objects within this grid.
	std::vector<GridObject*> objects;

	GridData(int id = 0) : ruleid(id) , elevation(0) {}

	void addObj(GridObject* obj);
	void delObj(GridObject* obj);
	bool isEmpty();

private:

};

#endif