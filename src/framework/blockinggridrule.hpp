#ifndef BLOCK_GRID_RULE_H
#define BLOCK_GRID_RULE_H

#include "gridrule.h"

class BlockingGridRule : public GridRule
{
private:

public:

	/**
	 * Returns true if all grid access should be denied.
	 */
	bool ignoreAll();

	/**
	 * Returns true projectiles are allowed access.
	 * 
	 * This rule is superceded by ignoreAll -funtion.
	 */
	bool allowProjectile();

	/**
	 * Returns true grid objects are allowed access.
	 * 
	 * This rule is superceded by ignoreAll -funtion.
	 */
	bool allowObject();

	/**
	 * Return true if given object id is black listed.
	 */
	bool isBlackListed(const int objectid);

	/**
 	 * Blacklist the object id. Will result in isBlackListed 
	 * returning true for the same id.
	 */
	void blackListId(const int objectid);

	/**
	 * Remove object id blacklisting.
	 */
	void deListId(const int objectid);
};

#endif // BLOCK_GRID_RULE_H
