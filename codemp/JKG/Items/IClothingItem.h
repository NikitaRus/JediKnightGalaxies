#ifndef __ICLOTHINGITEM_H
#define __ICLOTHINITEM_H

#include "../Item.h"

class IClothingItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
};

class IClothingItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	IClothingItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	friend class IClothingItemInstance;
};

#endif