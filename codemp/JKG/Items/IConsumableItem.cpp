#include "IConsumableItem.h"

/*
===============================
Item Class
===============================
*/

void IConsumableItem::ParseInventoryItem( void *cJSONNode )
{

}

/*
===============================
Item Instance Class
===============================
*/

IConsumableItemInstance::IConsumableItemInstance()
{
	iType = ITEM_CONSUMABLE;
}

SerializeCompare_m IConsumableItemInstance::CompareAgainst( BG_BUILD_INSTANCE *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}
}

SerializeCompare_m IConsumableItemInstance::FullRawString()
{
}

void IConsumableItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
}

void IConsumableItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
}