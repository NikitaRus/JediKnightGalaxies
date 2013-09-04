#include "IArmorItem.h"

/*
===============================
Item Class
===============================
*/

void IArmorItem::ParseInventoryItem( void *cJSONNode )
{

}

/*
===============================
Item Instance Class
===============================
*/

IArmorItemInstance::IArmorItemInstance()
{
	iType = ITEM_ARMOR;
}

SerializeCompare_m IArmorItemInstance::CompareAgainst( BG_BUILD_INSTANCE *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}
}

SerializeCompare_m IArmorItemInstance::FullRawString()
{
}

void IArmorItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
}

void IArmorItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
}