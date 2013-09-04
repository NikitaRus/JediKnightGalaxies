#include "ICrystalItem.h"

/*
===============================
Item Class
===============================
*/

void ICrystalItem::ParseInventoryItem( void *cJSONNode )
{

}

/*
===============================
Item Instance Class
===============================
*/

ICrystalItemInstance::ICrystalItemInstance()
{
	iType = ITEM_CRYSTAL;
}

SerializeCompare_m ICrystalItemInstance::CompareAgainst( BG_BUILD_INSTANCE *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}
}

SerializeCompare_m ICrystalItemInstance::FullRawString()
{
}

void ICrystalItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
}

void ICrystalItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
}