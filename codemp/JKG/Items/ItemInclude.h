#pragma once

// Has all of the item types included, good for the manager and other places where we need to access types

#include "IAmmoItem.h"
#include "IArmorItem.h"
#include "IClothingItem.h"
#include "IConsumableItem.h"
#include "ICrystalItem.h"
#include "IGenericItem.h"
#include "IWeaponItem.h"

typedef VMItemInstance*		(*instancefactoryfunc)();
typedef VMInventoryItem*	(*itemfactoryfunc)(void *cJSON);

typedef struct
{
	inventoryItemType_e		enumerator;
	std::string				name;
	instancefactoryfunc		instancefactory;
	itemfactoryfunc			itemfactory;
} itemTypeCallbacks_t;

itemTypeCallbacks_t itemTypes[] = {
	{ ITEM_UNKNOWN,		"generic",		(instancefactoryfunc)IGenericItemInstance::Factory,		(itemfactoryfunc)IGenericItem::Factory },
	{ ITEM_WEAPON,		"weapon",		(instancefactoryfunc)IWeaponItemInstance::Factory,		(itemfactoryfunc)IWeaponItem::Factory },
	{ ITEM_ARMOR,		"armor",		(instancefactoryfunc)IArmorItemInstance::Factory,		(itemfactoryfunc)IArmorItem::Factory },
	{ ITEM_CLOTHING,	"clothing",		(instancefactoryfunc)IClothingItemInstance::Factory,	(itemfactoryfunc)IClothingItem::Factory },
	{ ITEM_CRYSTAL,		"crystal",		(instancefactoryfunc)ICrystalItemInstance::Factory,		(itemfactoryfunc)ICrystalItem::Factory },
	{ ITEM_CONSUMABLE,	"consumable",	(instancefactoryfunc)IConsumableItemInstance::Factory,	(itemfactoryfunc)IConsumableItem::Factory },
	{ ITEM_AMMO,		"ammo",			(instancefactoryfunc)IAmmoItemInstance::Factory,		(itemfactoryfunc)IAmmoItem::Factory },
};
	