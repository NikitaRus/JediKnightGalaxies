#ifndef __ICRYSTALITEM_H
#define __ICRYSTALITEM_H

#include "../Item.h"

class ICrystalItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
};

class ICrystalItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	ICrystalItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	friend class ICrystalItemInstance;

	/* Custom stuff */
private:
	enum ikeys
	{
		ITMKEY_ITEMID,
		ITMKEY_UID,
		ITMKEY_MAX
	};
};

#endif