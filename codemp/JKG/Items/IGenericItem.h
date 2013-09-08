#ifndef __IGENERICITEM_H
#define __IGENERICITEM_H

#include "../ItemManager.h"
#ifdef QAGAME
#include "game/g_local.h"
#else
#include "cgame/cg_local.h"
#endif

class IGenericItem : public VMInventoryItem
{
	/* Stuff needed from the framework */
public:
	IGenericItem( void *cJSON );
	static IGenericItem* Factory( void *cJSON ) { return new IGenericItem( cJSON ); }
};

class IGenericItemInstance : public VMItemInstance
{
	/* Stuff needed from the framework */
public:
	IGenericItemInstance();
	SerializeCompare_m CompareAgainst( InventoryItemInstance *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	static IGenericItemInstance* Factory() { return new IGenericItemInstance(); }

friend class IGenericItemInstance;

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