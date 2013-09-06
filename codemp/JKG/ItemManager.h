#ifndef __ITEMMANAGER_H
#define __ITEMMANAGER_H

#include "Item.h"

class ItemManager
{
private:
	std::vector<BG_BUILD_ITEM *> lookupTable;
public:
	void ParseItemFiles( void );

	BG_BUILD_ITEM *ItemLookup( unsigned int id );
	BG_BUILD_ITEM *ItemLookup( std::string internalName );

	static void InitManager();
	static void ShutdownManager();
};

extern ItemManager *itmm;

#endif