#include "Item.h"

#ifndef QAGAME
#include "cgame/cg_local.h"
#else
#include "game/g_local.h"
#endif

class ItemManager
{
private:
	std::vector<BG_BUILD_ITEM> lookupTable;
public:
	void ParseItemFiles( void );

	BG_BUILD_ITEM *ItemLookup( unsigned int id );
	BG_BUILD_ITEM *ItemLookup( std::string internalName );
};

extern ItemManager *itmm;