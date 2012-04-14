#include "defaultgridrule.h"

bool DefaultGridRule::ignoreAll()
{
	return false;
}

bool DefaultGridRule::allowProjectile()
{
	return true;
}

bool DefaultGridRule::allowObject()
{
	return true;
}

bool DefaultGridRule::isBlackListed(const int objectid)
{
	bool found = false;
	for(int i=blacklist.size()-1;i>=0;--i)
	{
		if(blacklist[i]==objectid)
		{
			found = true;
			break;
		}
	}
	return found;
}

void DefaultGridRule::blackListId(const int objectid)
{
	blacklist.push_back(objectid);	
}

void DefaultGridRule::deListId(const int objectid)
{
	for(std::vector<int>::iterator it = blacklist.begin(); it != blacklist.end(); ++it)
	{
		if((*it)==objectid)
		{
			blacklist.erase(it);
			break;
		}
	}
}