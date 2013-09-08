#ifndef __ICRYSTALITEM_H
#define __ICRYSTALITEM_H

#include "../ItemManager.h"
#ifdef QAGAME
#include "game/g_local.h"
#else
#include "cgame/cg_local.h"
#endif

class ICrystalItem : public VMInventoryItem
{
	/* Stuff needed from the framework */
public:
	ICrystalItem( void *cJSON );
	static ICrystalItem* Factory( void *cJSON ) { return new ICrystalItem( cJSON ); }
};

class ICrystalItemInstance : public VMItemInstance
{
	/* Stuff needed from the framework */
public:
	ICrystalItemInstance();
	SerializeCompare_m CompareAgainst( InventoryItemInstance *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	static ICrystalItemInstance* Factory() { return new ICrystalItemInstance(); }

friend class ICrystalItemInstance;

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