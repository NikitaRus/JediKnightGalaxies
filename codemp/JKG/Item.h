#ifndef __ITEM_H
#define __ITEM_H

#include "qcommon/q_shared.h"

// This is done BG-wide. This is NOT accessed by the engine in any way.

// Inventory management

#ifdef QAGAME

// Gameside version

class GInventoryItem : public InventoryItem
{
public:
	std::string GetInternalName() { return internalName; }
	std::string GetDisplayName() { return displayName; }
};

class GItemInstance : public InventoryItemInstance
{
public:
	GInventoryItem *FillBaseData();
};

#define BG_BUILD_ITEM		GInventoryItem
#define BG_BUILD_INSTANCE	GItemInstance

#else

class CGInventoryItem : public InventoryItem
{
public:
	std::string GetInternalName() { return internalName; }
	std::string GetDisplayName() { return displayName; }
};

class CGItemInstance : public InventoryItemInstance
{
public:
	CGInventoryItem *FillBaseData();
};

#define BG_BUILD_ITEM		CGInventoryItem
#define BG_BUILD_INSTANCE	CGItemInstance

#endif

#endif