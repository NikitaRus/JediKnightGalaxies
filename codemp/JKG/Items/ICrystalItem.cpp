#include "ICrystalItem.h"

/*
===============================
Item Class
===============================
*/

ICrystalItem::ICrystalItem( void *cJSON )
{
	iType = ITEM_CRYSTAL;

	ItemManager::ParseGenericItemFields( this, cJSON );
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

SerializeCompare_m ICrystalItemInstance::CompareAgainst( InventoryItemInstance *other )
{
	if( other->GetItemType() != iType )
	{
		return FullRawString();
	}

	ICrystalItemInstance* cmp = static_cast<ICrystalItemInstance*>( other );
	SerializeCompare_m cmpString;

	// If our uIDs don't match, we should network this as an all-new item.
	if( cmp->uID != uID )
	{
		return FullRawString();
	}

	return cmpString;
}

SerializeCompare_m ICrystalItemInstance::FullRawString()
{
	SerializeCompare_m rawString;

	rawString[ITMKEY_ITEMID] = itemID;
	rawString[ITMKEY_UID] = uID;

	return rawString;
}

void ICrystalItemInstance::WriteDelta( SerializeCompare_m keylist, SerializeString_v *string )
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
		catch( const std::out_of_range & )
		{
			continue;
		}
	}
}

void ICrystalItemInstance::SetField( unsigned int fieldID, unsigned int value )
{
	switch( fieldID )
	{
		case ITMKEY_ITEMID:
			{
				itemID = value;
				VMInventoryItem *itm = FillBaseData();
				if(!itm) return;
				id = itm;
				break;
			}
		case ITMKEY_UID:
			uID = value;
			break;
	}
}