#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <algorithm>
#include "framework/gridrule.h"
#include "framework/defaultgridrule.h"
#include "framework/gridobject.h"
#include "framework/griddata.hpp"

#define X_TO_PX_RATIO 20
#define Y_TO_PX_RATIO 20

class World
{
private:
	GridData ***grid;

	int ROWS,COLUMNS;

	std::vector<GridRule*> rules;
	std::vector<GridObject*> objects;

	void updateObject(GridObject*);

public:
	World(int rows,int columns);

	/**
	 * update world with given float delta.
	 */
	void onStep(float delta);

	void addGridObject(GridObject*);

	std::vector<GridObject*> getGridObjects();

	int getGridHeight();

	int getGridWidth();

	int xToColumn(float x);

	float columnToX(int x);

	int yToRow(float y);

	float rowToY(int y);
};

#endif // WORLD_H
