#ifndef __ICONSUMABLEITEM_H
#define __ICONSUMABLEITEM_H

#include "../ItemManager.h"
#ifdef QAGAME
#include "game/g_local.h"
#else
#include "cgame/cg_local.h"
#endif

class IConsumableItem : public VMInventoryItem
{
	/* Stuff needed from the framework */
public:
	IConsumableItem( void *cJSON );
	static IConsumableItem* Factory( void *cJSON ) { return new IConsumableItem( cJSON ); }
};

class IConsumableItemInstance : public VMItemInstance
{
	/* Stuff needed from the framework */
public:
	IConsumableItemInstance();
	SerializeCompare_m CompareAgainst( InventoryItemInstance *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	static IConsumableItemInstance* Factory() { return new IConsumableItemInstance(); }

friend class IConsumableItemInstance;

	/* Custom stuff */
private:
	enum ikeys
	{
		ITMKEY_ITEMID,
		ITMKEY_UID,
		ITMKEY_MAX
	};
};

#endif