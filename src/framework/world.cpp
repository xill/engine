#include "framework/world.h"

World::World(int rows,int columns) : ROWS(rows) , COLUMNS(columns)
{
	grid = new GridData **[ROWS] ;
	for( int i = 0 ; i < ROWS ; ++i )
	{
		grid[i] = new GridData*[COLUMNS];
		for( int f = 0 ; f < COLUMNS ; ++f )
		{
			grid[i][f] = new GridData(0);
		}
	}

	rules.push_back(new DefaultGridRule());
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
				for(std::vector<GridObject*>::iterator it = data->objects.begin(); it != data->objects.end(); ++it)
				{
					int x = (*it)->getXOffset();
					int y = (*it)->getYOffset();

					// if no movement. no need to update.
					if(x == 0 && y == 0) continue;
					
					int resRow = row + y;
					int resCol = col + x;
					
					if(resRow < 0) resRow = 0;
					else if(resRow >= ROWS) resRow = ROWS - 1;

					if(resCol < 0) resCol = 0;
					else if(resCol >= COLUMNS) resCol = COLUMNS - 1;

					GridData* destGrid = grid[resRow][resCol];

					// checks if rules deem movement possible.
					GridRule* rule = rules[destGrid->ruleid];

					if(rule->ignoreAll()) continue;

					if(rule->isBlackListed((*it)->getId())) continue;

					switch((*it)->getType())
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

					(*it)->setGridX(resCol);
					(*it)->setGridY(resRow);

					data->delObj((*it));
					destGrid->addObj((*it));
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
}

std::vector<GridObject*> World::getGridObjects()
{
	return objects;
}

int World::xToColumn(float x)
{
	return x/X_TO_PX_RATIO;
}

int World::yToRow(float y)
{
	return y/Y_TO_PX_RATIO;
}

float World::columnToX(int x)
{
	return ((float)x)*X_TO_PX_RATIO + X_TO_PX_RATIO * 0.5f;
}

float World::rowToY(int y)
{
	return ((float)y)*Y_TO_PX_RATIO + Y_TO_PX_RATIO * 0.5f;
}
