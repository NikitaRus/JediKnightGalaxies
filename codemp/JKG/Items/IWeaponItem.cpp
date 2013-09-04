#include "IWeaponItem.h"

/*
===============================
Item Class
===============================
*/

void IWeaponItem::ParseInventoryItem( void *cJSONNode )
{
	// No parsing yet.
	return;
}

/*
===============================
Item Instance Class
===============================
*/

IWeaponItemInstance::IWeaponItemInstance()
{
	iType = ITEM_WEAPON;
}

SerializeCompare_m IWeaponItemInstance::CompareAgainst( BG_BUILD_INSTANCE *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}
}

SerializeCompare_m IWeaponItemInstance::FullRawString()
{
}

void IWeaponItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
}

void IWeaponItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
}