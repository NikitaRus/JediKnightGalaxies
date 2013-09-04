#ifndef __ITEM_H
#define __ITEM_H

#include "qcommon/q_shared.h"
#include "ItemManager.h"

// This is done BG-wide. This is NOT accessed by the engine in any way.

// Inventory management

extern ItemManager *itmm;

#ifdef QAGAME

// Gameside version

class GInventoryItem : public InventoryItem
{
public:
};

class GItemInstance : public InventoryItemInstance
{
public:
	GInventoryItem *FillBaseData() 
	{
		if( itemID < 0 )
			return NULL;
		return itmm->ItemLookup( itemID );
	}
};

#define BG_BUILD_ITEM		GInventoryItem
#define BG_BUILD_INSTANCE	GItemInstance

#else

class CGInventoryItem : public InventoryItem
{
public:
};

class CGItemInstance : public InventoryItemInstance
{
public:
	CGInventoryItem *FillBaseData() 
	{
		if( itemID < 0 )
			return NULL;
		return itmm->ItemLookup( itemID );
	}
};

#define BG_BUILD_ITEM		CGInventoryItem
#define BG_BUILD_INSTANCE	CGItemInstance

#endif

#endif