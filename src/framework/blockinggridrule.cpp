#include "blockinggridrule.hpp"

bool BlockingGridRule::ignoreAll()
{
	return true;
}

bool BlockingGridRule::allowProjectile()
{
	return false;
}

bool BlockingGridRule::allowObject()
{
	return false;
}

bool BlockingGridRule::isBlackListed(const int objectid)
{
	return true;
}

void BlockingGridRule::blackListId(const int objectid)
{

}

void BlockingGridRule::deListId(const int objectid)
{

}