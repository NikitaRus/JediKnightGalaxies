#ifndef __IARMORITEM_H
#define __IARMORITEM_H

#include "../ItemManager.h"
#ifdef QAGAME
#include "game/g_local.h"
#else
#include "cgame/cg_local.h"
#endif

class IArmorItem : public VMInventoryItem
{
	/* Stuff needed from the framework */
public:
	IArmorItem( void *cJSON );
	static IArmorItem* Factory( void *cJSON ) { return new IArmorItem( cJSON ); }
	/* Custom stuff */
private:
	int armorSlot;
	int armorId;
};

class IArmorItemInstance : public VMItemInstance
{
	/* Stuff needed from the framework */
public:
	IArmorItemInstance();
	SerializeCompare_m CompareAgainst( InventoryItemInstance *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	static IArmorItemInstance* Factory() { return new IArmorItemInstance(); }

friend class IArmorItemInstance;

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