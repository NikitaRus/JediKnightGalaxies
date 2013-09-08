#include "q_shared.h"
#include "qcommon.h"

ID_INLINE void _generateHiLo( short value, unsigned char *hi, unsigned char *lo )
{
	if( !hi || !lo ) return;
	*hi = (value >> 8) & 0xf;
	*lo = value & 0xf;
}

SerializeString_v InventoryNetworker::GenerateDeltaData( Inventory *oldInv, Inventory *newInv )
{
	SerializeString_v retVal;
	unsigned short oldNumberItems = oldInv->GetNumberItems();
	unsigned short newNumberItems = newInv->GetNumberItems();
	bool newItems = ( oldNumberItems < newNumberItems );
	bool lessItems = ( oldNumberItems > newNumberItems );
	bool delta = ( newItems || lessItems );
	unsigned char hi = 0, lo = 0;
	std::map<unsigned int, SerializeCompare_m> changedItemsAndValues;
	unsigned int i;

	// If we have new/less items, we need to figure out where those changes are
	for( i = 0; i < newNumberItems; i++ )
	{
		if( i < oldNumberItems )
		{
			// Listing any changes in the non-new items
			InventoryItemInstance *itm1 = oldInv->GetItemAt( i );
			InventoryItemInstance *itm2 = newInv->GetItemAt( i );
			if( itm1->uID != itm2->uID )
			{
				// completely different item, don't even bother at this point..
				changedItemsAndValues[i] = itm2->FullRawString();
			}
			else
			{
				// Two items are different here.
				SerializeCompare_m itmComparison = itm1->CompareAgainst( itm2 );
				if( itmComparison.size() > 0 )
				{
					// There's a difference here.
					delta = true;
					changedItemsAndValues[i] = itmComparison;
					continue;
				}
			}
		}
		else
		{
			// Listing the new items
			changedItemsAndValues[i] = newInv->GetItemAt( i )->FullRawString();
		}
	}

	if( !delta )
	{
		retVal.push_back( 0xFF );
		retVal.push_back( 0xFF );
	}
	else
	{
		_generateHiLo( newNumberItems, &hi, &lo );
		retVal.push_back( lo );
		retVal.push_back( hi );

		// very simple -- we're changing a stat on an item
		for( i = 0; i < newNumberItems; i++ )
		{
			try
			{
				SerializeCompare_m keylist = changedItemsAndValues.at(i);

				// We have a change
				InventoryItemInstance *itm = newInv->GetItemAt( i );
				itm->WriteDelta( keylist, &retVal );
			}
			catch( const std::out_of_range & )
			{
				// No change in this item
				retVal.push_back(0xFF);
				continue;
			}
		}
	}


	return retVal;
}

void InventoryNetworker::PushDeltaData( msg_t *msg, SerializeString_v data )
{
	// Iterate through the data and write a byte for each object
	for( auto it = data.begin(); it != data.end(); ++it )
	{
		MSG_WriteByte( msg, *it );
	}
}

void InventoryNetworker::PopDeltaData( msg_t *msg, Inventory *oldInv, Inventory *newInv )
{
	// Read number of items
	int i, j;
	int numItemsNew = MSG_ReadShort(msg);

	memcpy( newInv, oldInv, sizeof( Inventory ) );

	if( numItemsNew == -1 )
		return;	// nothin to see here

	// Read from the MSG buffer
	for( i = 0; i < numItemsNew; i++ )
	{
		// we're dealing with an old field, just possibly changed.
		if( i >= oldInv->items.size() )
		{
			int numChangedFields = MSG_ReadByte(msg);
			if( numChangedFields == -1 )
			{
				continue;	// no change
			}
			else
			{
				// Change in fields
				InventoryItemInstance *itm = oldInv->GetItemAt( i );
				for( j = 0; j < numChangedFields; j++ )
				{
					itm->SetField( MSG_ReadByte(msg), MSG_ReadShort(msg) );
				}
			}
		}
		else
		{
			// adding new fields
		}
	}
}