#include "IGenericItem.h"

/*
===============================
Item Class
===============================
*/

void IGenericItem::ParseInventoryItem( void *cJSONNode )
{
	// No parsing yet.
	return;
}

/*
===============================
Item Instance Class
===============================
*/

IGenericItemInstance::IGenericItemInstance()
{
	iType = ITEM_NONE;
}

SerializeCompare_m IGenericItemInstance::CompareAgainst( BG_BUILD_INSTANCE *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}
}

SerializeCompare_m IGenericItemInstance::FullRawString()
{
}

void IGenericItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
}

void IGenericItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
}