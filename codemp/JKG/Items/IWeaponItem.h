#ifndef __IWEAPONITEM_H
#define __IWEAPONITEM_H

#include "../Item.h"

/*
===============================
Item Class
===============================
*/

class IWeaponItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
};

/*
===============================
Item Instance Class
===============================
*/

class IWeaponItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	IWeaponItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	friend class IWeaponItemInstance;
};

#endif