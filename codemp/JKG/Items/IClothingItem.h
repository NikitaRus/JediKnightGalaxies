#ifndef __ICLOTHINGITEM_H
#define __ICLOTHINITEM_H

#include "../ItemManager.h"
#ifdef QAGAME
#include "game/g_local.h"
#else
#include "cgame/cg_local.h"
#endif

class IClothingItem : public VMInventoryItem
{
	/* Stuff needed from the framework */
public:
	IClothingItem( void *cJSON );
	static IClothingItem* Factory( void *cJSON ) { return new IClothingItem( cJSON ); }
};

class IClothingItemInstance : public VMItemInstance
{
	/* Stuff needed from the framework */
public:
	IClothingItemInstance();
	SerializeCompare_m CompareAgainst( InventoryItemInstance *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	static IClothingItemInstance* Factory() { return new IClothingItemInstance(); }

friend class IClothingItemInstance;

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