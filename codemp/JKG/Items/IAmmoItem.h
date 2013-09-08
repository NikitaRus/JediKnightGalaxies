#ifndef __IAMMOITEM_H
#define __IAMMOITEM_H

#include "../ItemManager.h"
#ifdef QAGAME
#include "game/g_local.h"
#else
#include "cgame/cg_local.h"
#endif

class IAmmoItem : public VMInventoryItem
{
	/* Stuff needed from the framework */
public:
	IAmmoItem( void *cJSON );
	static IAmmoItem* Factory( void *cJSON ) { return new IAmmoItem( cJSON ); }
};

class IAmmoItemInstance : public VMItemInstance
{
	/* Stuff needed from the framework */
public:
	IAmmoItemInstance();
	SerializeCompare_m CompareAgainst( InventoryItemInstance *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	static IAmmoItemInstance* Factory() { return new IAmmoItemInstance(); }

friend class IAmmoItemInstance;

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