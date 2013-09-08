#ifndef __IWEAPONITEM_H
#define __IWEAPONITEM_H

#include "../ItemManager.h"

/*
===============================
Item Class
===============================
*/

class IWeaponItem : public VMInventoryItem
{
	/* Stuff needed from the framework */
public:
	IWeaponItem( void *cJSON );
	static IWeaponItem* Factory(void *cJSONNode) { return new IWeaponItem(cJSONNode); }
	/* Custom stuff */
private:
	int weapon;
	int variation;
	int varID;
	std::string xml; // FIXME: remove, this blows donkey dildos
};

/*
===============================
Item Instance Class
===============================
*/

class IWeaponItemInstance : public VMItemInstance
{
	/* Stuff needed from the framework */
public:
	IWeaponItemInstance();
	SerializeCompare_m CompareAgainst( InventoryItemInstance *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	static IWeaponItemInstance* Factory() { return new IWeaponItemInstance(); }

friend class IWeaponItemInstance;

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