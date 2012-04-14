#include "framework/world.h"

World::World(int rows,int columns) : ROWS(rows) , COLUMNS(columns)
{
	// should the grid be constructed from a outside source.
	grid = new GridData **[ROWS] ;
	for( int i = 0 ; i < ROWS ; ++i )
	{
		grid[i] = new GridData*[COLUMNS];
		for( int f = 0 ; f < COLUMNS ; ++f )
		{
			if(columns > 7 && f == 7 && i != rows-1)
			{
				grid[i][f] = new GridData(1);
			}
			else {
				grid[i][f] = new GridData(0);
			}
		}
	}

	rules.push_back(new DefaultGridRule());
	rules.push_back(new BlockingGridRule());
}

void World::onStep(float delta)
{
	for(int row = 0 ; row < ROWS ; ++row)
	{
		for(int col = 0 ; col < COLUMNS ; ++col)
		{
			GridData* data = grid[row][col];

			if(!data->isEmpty())
			{
				for(int i = 0 ; i < objects.size() ; ++i)
				{
					GridObject* obj = objects[i];
					int x = obj->getXOffset();
					int y = obj->getYOffset();

					// if no movement. no need to update.
					if(x == 0 && y == 0) continue;
					
					int resRow = row + y;
					int resCol = col + x;

					// resets the movement.
					obj->setDesiredGridOffset();
					
					if(resRow < 0) resRow = 0;
					else if(resRow >= ROWS) resRow = ROWS - 1;

					if(resCol < 0) resCol = 0;
					else if(resCol >= COLUMNS) resCol = COLUMNS - 1;

					GridData* destGrid = grid[resRow][resCol];

					// checks if rules deem movement possible.
					GridRule* rule = rules[destGrid->ruleid];

					if(rule->ignoreAll()) continue;

					if(rule->isBlackListed(obj->getId())) continue;

					switch(obj->getType())
					{
					case PROJECTILE:
						if(!rule->allowProjectile())
						{
							continue;
						}
						break;
					case OBJECT:
						if(!rule->allowObject())
						{
							continue;
						}
						break;
					};

					obj->setGridX(resCol);
					obj->setGridY(resRow);

					data->delObj(obj);
					destGrid->addObj(obj);

					// debug stuff
					obj->setX(columnToX(obj->getGridX()));
					obj->setY(rowToY(obj->getGridY()));
					// debug stuff end.
				}
			}
		}
	}
}

void World::updateObject(GridObject*)
{

}

void World::addGridObject(GridObject* obj)
{
	objects.push_back(obj);
	grid[obj->getGridY()][obj->getGridX()]->addObj(obj);

	obj->setX(columnToX(obj->getGridX()));
	obj->setY(rowToY(obj->getGridY()));
}

std::vector<GridObject*> World::getGridObjects()
{
	return objects;
}

std::vector<GridRule*> World::getRuleSet()
{
	return rules;
}

GridData*** World::getGrid()
{
	return grid;
}

int World::getGridHeight()
{
	return ROWS;
}

int World::getGridWidth()
{
	return COLUMNS;
}

int World::xToColumn(float x)
{
	return (int) (x/X_TO_PX_RATIO);
}

int World::yToRow(float y)
{
	return (int) (y/Y_TO_PX_RATIO);
}

float World::columnToX(int x)
{
	return ((float)x)*X_TO_PX_RATIO + X_TO_PX_RATIO * 0.5f;
}

float World::rowToY(int y)
{
	return ((float)y)*Y_TO_PX_RATIO + Y_TO_PX_RATIO * 0.5f;
}
