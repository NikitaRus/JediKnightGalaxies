#include "IClothingItem.h"

/*
===============================
Item Class
===============================
*/

void IClothingItem::ParseInventoryItem( void *cJSONNode )
{

}

/*
===============================
Item Instance Class
===============================
*/

IClothingItemInstance::IClothingItemInstance()
{
	iType = ITEM_CLOTHING;
}

SerializeCompare_m IClothingItemInstance::CompareAgainst( BG_BUILD_INSTANCE *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}
}

SerializeCompare_m IClothingItemInstance::FullRawString()
{
}

void IClothingItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
}

void IClothingItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
}