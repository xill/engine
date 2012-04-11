#ifndef GRID_RULE_H
#define GRID_RULE_H

class GridRule
{
protected:

public:

	/**
	 * Returns true if all grid access should be denied.
	 */
	virtual bool ignoreAll() = 0;

	/**
	 * Returns true projectiles are allowed access.
	 * 
	 * This rule is superceded by ignoreAll -funtion.
	 */
	virtual bool allowProjectile() = 0;

	/**
	 * Returns true grid objects are allowed access.
	 * 
	 * This rule is superceded by ignoreAll -funtion.
	 */
	virtual bool allowObject() = 0;

	/**
	 * Return true if given object id is black listed.
	 */
	virtual bool isBlackListed(const int objectid) = 0;

	/**
 * Blacklist the object id. Will result in isBlackListed 
 * returning true for the same id.
 */
	virtual void blackListId(const int objectid) = 0;

	/**
 * Remove object id blacklisting.
 */
	virtual void deListId(const int objectid) = 0;
};

#endif // GRID_RULE_H
