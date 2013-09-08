#ifndef __ITEMMANAGER_H
#define __ITEMMANAGER_H

#include "qcommon/q_shared.h"
#include <json/cJSON.h>
#include "ItemManager.h"

// This is done BG-wide. This is NOT accessed by the engine in any way.

// Inventory management

// Gameside version

class VMInventoryItem : public InventoryItem
{
protected:
	int iType;			// gets chucked into the instance later on
	int itemID;

#ifndef QAGAME
	std::string iconpath;
#endif
	int baseCost;
	int weight;
public:
	std::string GetInternalName() { return internalName; }
	std::string GetDisplayName() { return displayName; }
	int GetItemType() { return iType; }

friend class ItemManager;
};

class VMItemInstance : public InventoryItemInstance
{
public:
	VMInventoryItem *FillBaseData();
	int				_itmmid;		/// do NOT use
	int				itemID;			// gets chucked in from the base item
};

class ItemManager
{
private:
	std::vector<VMInventoryItem *> lookupTable;
	std::vector<VMItemInstance *> instanceManager;
	int last_itmid;
public:
	void ParseItemFiles( void );

	VMInventoryItem *ItemLookup( unsigned int id );
	VMInventoryItem *ItemLookup( std::string internalName );

	VMItemInstance *GenerateItemInstance( unsigned int itemID, SerializeCompare_m *values = (SerializeCompare_m *)0 );
	void GCItemInstance( VMItemInstance *item );

	static void InitManager();
	static void ShutdownManager();

	static void ParseGenericItemFields( VMInventoryItem *item, void *cJSONRoot );
};

extern ItemManager *itmm;

#endif