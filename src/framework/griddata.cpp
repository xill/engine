#include "griddata.hpp"

void GridData::addObj(GridObject* obj)
{
	objects.push_back(obj);
}
	
void GridData::delObj(GridObject* obj)
{
	if(!isEmpty())
	{
		for(std::vector<GridObject*>::iterator it = objects.begin() ; it != objects.end() ; ++it )
		{
			if((*it) == obj)
			{
				objects.erase(it);
				break;
			}
		}
	}
}
	
bool GridData::isEmpty()
{
	return (objects.size() == 0);
}