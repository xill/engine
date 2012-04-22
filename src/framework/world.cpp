#include "framework/world.h"

World::World(int rows,int columns) : ROWS(rows) , COLUMNS(columns)
{
	// should the grid be constructed from a outside source.
	grid = new GridData **[ROWS] ;
	float elevation = 0;
	float deelevecation = 0;
	for( int i = 0 ; i < ROWS ; ++i )
	{
		grid[i] = new GridData*[COLUMNS];
		for( int f = 0 ; f < COLUMNS ; ++f )
		{
			if(columns > 7 && f == 7 && i != rows-1)
			{
				grid[i][f] = new GridData(1);
			}
			else if(f == 0)
			{
				// ladder up.
				grid[i][f] = new GridData(0);
				grid[i][f]->elevation = elevation;
				elevation -= 3;
			}
			else if(f == columns - 1)
			{
				// ladder down.
				grid[i][f] = new GridData(0);
				grid[i][f]->elevation = deelevecation;
				deelevecation += 3;
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
				for(int i = 0 ; i < data->objects.size() ; ++i)
				{
					GridObject* obj = data->objects[i];

					float t_x = columnToX(col)
						,t_y = rowToY(row);

					if(obj->tweenTo(t_x,t_y,data->elevation,delta))
					{
						continue; 
					}

					obj->setZ(data->elevation);

					int x = obj->getXOffset();
					int y = obj->getYOffset();

					// if no movement. no need to update.
					if(x == 0 && y == 0) continue;
					
					int resRow = row + y;
					int resCol = col + x;
					
					if(resRow < 0) resRow = 0;
					else if(resRow >= ROWS) resRow = ROWS - 1;

					if(resCol < 0) resCol = 0;
					else if(resCol >= COLUMNS) resCol = COLUMNS - 1;

					GridData* destGrid = grid[resRow][resCol];

					// check if the objects in the grid wish to share it.
					bool share = true;

					if(!destGrid->isEmpty())
					{
						for(std::vector<GridObject*>::iterator it = destGrid->objects.begin() ; it != destGrid->objects.end() ; ++it )
						{
							if(!(*it)->canShareGrid())
							{
								share = false;
								break;
							}
						}
					}

					if(!share) continue;

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

					float diff = destGrid->elevation - data->elevation;

					if(diff != 0 && ((diff < 0)?diff*-1:diff) > obj->getZMaxDiff()) continue;

					obj->setGridX(resCol);
					obj->setGridY(resRow);

					switch(obj->getZType())
					{
					case AUTO:
						{
							if(diff != 0)
							{
								float timesToReach = 0;
								float c = 0;
								if(x != 0) { timesToReach += X_TO_PX_RATIO; c++; }
								if(y != 0) { timesToReach += Y_TO_PX_RATIO; c++; }

								if(c > 1)
								{
									timesToReach /= c;
								}

								timesToReach /= obj->getGridMovementSpeed();
								obj->setZMovementSpeed(diff/timesToReach);
							}
						}
						break;
					case SNAP:
						obj->setZ(destGrid->elevation);
						break;
					default:
						break;
					}

					data->delObj(obj);
					destGrid->addObj(obj);
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
