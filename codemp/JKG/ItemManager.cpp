#include "ItemManager.h"
#include "Items/ItemInclude.h"

#ifdef QAGAME
#include "game/g_local.h"
#else
#include "cgame/cg_local.h"
#endif

ItemManager *itmm = NULL;

/*
=================================
Common Functions
=================================
*/

__declspec(nothrow) inventoryItemType_e __fastcall StringToItemType( const char *text )
{
	for( int i = ITEM_UNKNOWN; i < ITEM_MAX; i++ )
	{
		if( !Q_stricmp(itemTypes[i].name.c_str(), text) )
		{
			return (inventoryItemType_e)i;
		}
	}
	return ITEM_UNKNOWN;
}

VMInventoryItem *VMItemInstance::FillBaseData()
{
	if( itemID < 0 )
		return NULL;
	return itmm->ItemLookup( itemID );
}

/*
=================================
ItemManager Class
=================================
*/

void ItemManager::InitManager()
{
	itmm = new ItemManager();
	itmm->ParseItemFiles();
	itmm->last_itmid = 0;
}

void ItemManager::ShutdownManager()
{
	for( auto it=itmm->instanceManager.begin(); it != itmm->instanceManager.end(); ++it )
	{
		delete *it;
	}
	itmm->instanceManager.clear();
	for( auto it=itmm->lookupTable.begin(); it != itmm->lookupTable.end(); ++it )
	{
		delete *it;
	}
	itmm->lookupTable.clear();
	delete itmm;
}

VMInventoryItem *ItemManager::ItemLookup( unsigned int id )
{
	try
	{
		return lookupTable.at(id);
	}
	catch( const std::out_of_range&  )
	{
		return NULL;
	}
}

VMInventoryItem *ItemManager::ItemLookup( std::string internalName )
{
	for( auto it=lookupTable.begin(); it != lookupTable.end(); ++it )
	{
		if( (*it)->GetInternalName() == internalName )
		{
			return *it;
		}
	}
	return NULL;
}

VMItemInstance* ItemManager::GenerateItemInstance( unsigned int itemID, SerializeCompare_m *values )
{
	VMInventoryItem *itmBase = ItemLookup( itemID );
	if( itmBase == NULL ) return NULL;
	VMItemInstance *itm = itemTypes[itmBase->GetItemType()].instancefactory();

	itm->_generateuid(-1);
	itm->_itmmid = last_itmid++;
	itm->FillBaseData();

	if( values != NULL )
	{
		// use the values listed
		for(auto it=values->begin(); it != values->end(); ++it)
		{
			itm->SetField( it->first, it->second );
		}
	}
	return itm;
}

void ItemManager::GCItemInstance( VMItemInstance *itm )
{
	if( itm->_itmmid >= instanceManager.size() )
		return;

	instanceManager.erase(instanceManager.begin() + itm->_itmmid);
	delete itm;
}

void ItemManager::ParseItemFiles( void )
{
	int i;
	char itemFiles[8192];
	int numFiles = trap_FS_GetFileList("ext_data/items/", ".itm", itemFiles, sizeof(itemFiles));
	int failed = 0, succeeded = 0;
	const char *itemFile = itemFiles;

	if( numFiles <= 0 || itemFile == NULL )
	{
		Com_Printf("No items detected.\n");
		return;
	}

	Com_Printf("Loading items...\n");
	for( i = 0; i < numFiles; i++, itemFile += strlen(itemFile)+1 )
	{
		// Basic file I/O for each file
		cJSON *json;
		fileHandle_t f;
		char error[1024] = {0};
		char itemFileData[16384] = {0};
		int fileLen = trap_FS_FOpenFile(itemFile, &f, FS_READ);

		if( f <= 0 ) {									failed++; continue; }
		if( fileLen <= 0 ) { trap_FS_FCloseFile(f);		failed++; continue; }
		if( fileLen >= 16384 ) { trap_FS_FCloseFile(f); failed++; continue; }

		trap_FS_Read(&itemFileData, fileLen, f);
		itemFileData[fileLen] = '\0';
		trap_FS_FCloseFile(f);

		json = cJSON_ParsePooled( itemFileData, error, sizeof(error) );
		if( json == NULL )
		{
			Com_Printf("^1%s: %s\n", itemFile, error);
			failed++;
			continue;
		}

		// Construct the item.
		int iType = StringToItemType( cJSON_ToString(cJSON_GetObjectItem (json, "itemtype")) );
		VMInventoryItem *itm = itemTypes[iType].itemfactory( (void *)json );
		lookupTable.push_back( itm );

		succeeded++;
		cJSON_Delete(json);
	}

	Com_Printf("%i succeeded, %i failed (%i total).\n", succeeded, failed, succeeded+failed);
}

void ItemManager::ParseGenericItemFields( VMInventoryItem *item, void *cJSONRoot )
{
	item->displayName = cJSON_ToString( cJSON_GetObjectItem( cJSONRoot, "name" ) );
	item->internalName = cJSON_ToString( cJSON_GetObjectItem( cJSONRoot, "internal" ) );
	item->itemID = cJSON_ToInteger( cJSON_GetObjectItem( cJSONRoot, "id" ) );
	item->baseCost = cJSON_ToInteger( cJSON_GetObjectItem( cJSONRoot, "cost" ) );
	item->weight = cJSON_ToInteger( cJSON_GetObjectItem( cJSONRoot, "weight" ) );

#ifndef QAGAME
	item->iconpath = cJSON_ToString( cJSON_GetObjectItem( cJSONRoot, "itemIcon" ) );
#endif
}