#ifndef GRIDDATA_HPP
#define GRIDDATA_HPP

#include <vector>
#include "gridobject.h"

class GridData
{
public:
	int ruleid;
	std::vector<GridObject*> objects;

	GridData(int id = 0) : ruleid(id) {}

	void addObj(GridObject* obj);
	void delObj(GridObject* obj);
	bool isEmpty();

private:

};

#endif