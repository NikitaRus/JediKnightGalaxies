#ifndef __IGENERICITEM_H
#define __IGENERICITEM_H

#include "../Item.h"

class IGenericItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
};

class IGenericItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	IGenericItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	friend class IGenericItemInstance;
};

#endif