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

	IClothingItemInstance* cmp = static_cast<IClothingItemInstance*>( other );
	SerializeCompare_m cmpString;

	// If our uIDs don't match, we should network this as an all-new item.
	if( cmp->uID != uID )
	{
		return FullRawString();
	}

	return cmpString;
}

SerializeCompare_m IClothingItemInstance::FullRawString()
{
	SerializeCompare_m rawString;

	rawString[ITMKEY_ITEMID] = itemID;
	rawString[ITMKEY_UID] = uID;

	return rawString;
}

void IClothingItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
{
	int i;
	for( i = 0; i < ITMKEY_MAX; i++ )
	{
		try
		{
			// Attempt to get the key for this value (if we fail, just try a different key value)
			short value = keylist[i];

			// Push back the key
			string->push_back(i);

			// Push back the value (and since it's a short, we push back the low bits and then the high bits)
			string->push_back( value & 0xF );			// lo bits
			string->push_back( (value >> 8) & 0xF );	// hi bits
		}
		catch( const std::out_of_range &oor )
		{
			continue;
		}
	}
}

void IClothingItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
	switch( fieldID )
	{
		case ITMKEY_ITEMID:
			{
				itemID = value;
				BG_BUILD_ITEM *itm = FillBaseData();
				if(!itm) return;
				id = itm;
				break;
			}
		case ITMKEY_UID:
			uID = value;
			break;
	}
}