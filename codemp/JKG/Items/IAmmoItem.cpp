#include "IAmmoItem.h"

/*
===============================
Item Class
===============================
*/

void IAmmoItem::ParseInventoryItem( void *cJSONNode )
{

}

/*
===============================
Item Instance Class
===============================
*/

IAmmoItemInstance::IAmmoItemInstance()
{
	iType = ITEM_AMMO;
}

SerializeCompare_m IAmmoItemInstance::CompareAgainst( BG_BUILD_INSTANCE *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}
}

SerializeCompare_m IAmmoItemInstance::FullRawString()
{
}

void IAmmoItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
}

void IAmmoItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
}