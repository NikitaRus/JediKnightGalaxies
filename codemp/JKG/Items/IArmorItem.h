#ifndef __IARMORITEM_H
#define __IARMORITEM_H

#include "../Item.h"

class IArmorItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
private:
};

class IArmorItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	IArmorItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );

	friend class IArmorItemInstance;

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