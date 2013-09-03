//       ____ ___________________   ___           ____  __ _______   ___  ________  ___ ______________
//      |    |\_   _____/\______ \ |   |         |    |/ _|\      \ |   |/  _____/ /   |   \__    ___/
//      |    | |    __)_  |    |  \|   |         |      <  /   |   \|   /   \  ___/    ~    \|    |   
//  /\__|    | |        \ |    `   \   |         |    |  \/    |    \   \    \_\  \    Y    /|    |   
//  \________|/_______  //_______  /___|         |____|__ \____|__  /___|\______  /\___|_  / |____|   
//                    \/         \/                      \/       \/            \/       \/           
//                         ________    _____   ____       _____  ____  ___ ______________ _________   
//                        /  _____/   /  _  \ |    |     /  _  \ \   \/  /|   \_   _____//   _____/   
//                       /   \  ___  /  /_\  \|    |    /  /_\  \ \     / |   ||    __)_ \_____  \    
//                       \    \_\  \/    |    \    |___/    |    \/     \ |   ||        \/        \   
//                        \______  /\____|__  /_______ \____|__  /___/\  \|___/_______  /_______  /   
//                               \/         \/        \/	   \/	   \_/			  \/        \/ (c)
// bg_items.h
// Loader for the .itm and .loot (obsolete) formats
// (c) 2013 Jedi Knight Galaxies

#ifndef BG_ITEMS_H
#define BG_ITEMS_H

#include "qcommon/q_shared.h"

#define MAX_ITEM_TABLE_SIZE     (65535)
#define MAX_ITEM_FILE_LENGTH    (16384)
#define MAX_ITEM_NAME			(64)
#define MAX_INVENTORY_ITEMS		(256)

#define MAX_PSPELLS				(10)
#define MAX_ACI_SLOTS			(10)

typedef enum
{
    PSPELL_NONE,
	PSPELL_ADD_PS,
	PSPELL_SUB_PS,
	PSPELL_MUL_PS,
	PSPELL_DIV_PS,
	PSPELL_EXP_PS,
	PSPELL_SQT_PS,
	PSPELL_ADD_CS,
	PSPELL_SUB_CS,
	PSPELL_MUL_CS,
	PSPELL_DIV_CS,
	PSPELL_EXP_CS,
	PSPELL_SQT_CS,
	PSPELL_SEEKER,
	PSPELL_PLAYSOUND,
	PSPELL_DESTROYITEM,
	PSPELL_CND_GT_PS,
	PSPELL_CND_EQ_PS,
	PSPELL_CND_LT_PS,
	PSPELL_CND_GT_CS,
	PSPELL_CND_EQ_CS,
	PSPELL_CND_LT_CS,
	PSPELL_DO_EVENT,
	PSPELL_MAX
} pSpell_t;

void BG_LoadDefaultWeaponItems ( void );
qboolean BG_HasWeaponItem ( int clientNum, int weaponId );

// Inventory management

#ifdef QAGAME

// Gameside version

class GInventoryItem : public InventoryItem
{
public:
};

class GItemInstance : public InventoryItemInstance
{
public:
};

#define BG_BUILD_ITEM		GInventoryItem
#define BG_BUILD_INSTANCE	GItemInstance

#else

class CGInventoryItem : public InventoryItem
{
public:
};

class CGItemInstance : public InventoryItemInstance
{
public:
};

#define BG_BUILD_ITEM		CGInventoryItem
#define BG_BUILD_INSTANCE	CGItemInstance

#endif

// Definitions for each of the basic types

/* Weapons */

class IWeaponItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
};

class IWeaponItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	IWeaponItem *FillBaseData();
	IWeaponItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );
};

/* Armor */

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
	IArmorItem *FillBaseData();
	IArmorItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );
};

/* Clothing */

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
	IClothingItem *FillBaseData();
	IClothingItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );
};

/* Lightsaber Crystals */

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
	ICrystalItem *FillBaseData();
	ICrystalItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );
};

/* Consumable Items */

class IConsumableItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
};

class IConsumableItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	IConsumableItem *FillBaseData();
	IConsumableItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );
};

/* Ammo */

class IAmmoItem : public BG_BUILD_ITEM
{
	/* Stuff needed from the framework */
public:
	void ParseInventoryItem( void *cJSONNode );
};

class IAmmoItemInstance : public BG_BUILD_INSTANCE
{
	/* Stuff needed from the framework */
public:
	IAmmoItem *FillBaseData();
	IAmmoItemInstance();
	SerializeCompare_m CompareAgainst( BG_BUILD_INSTANCE *other );
	SerializeCompare_m FullRawString( );
	void WriteDelta( SerializeCompare_m keylist, SerializeString_v *string );
	void SetField( unsigned int fieldID, unsigned int value );
};

#endif
