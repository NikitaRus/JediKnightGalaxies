#include "ItemManager.h"
#include "Item.h"

ItemManager *itmm = NULL;

void ItemManager::InitManager()
{
	itmm = new ItemManager();
	itmm->ParseItemFiles();
}

void ItemManager::ShutdownManager()
{
	delete itmm;
}

void ItemManager::ParseItemFiles( void )
{

}

BG_BUILD_ITEM *ItemManager::ItemLookup( unsigned int id )
{
	try
	{
		return lookupTable.at(id);
	}
	catch( const std::out_of_range& oob )
	{
		return NULL;
	}
}

BG_BUILD_ITEM *ItemManager::ItemLookup( std::string internalName )
{
	std::vector<BG_BUILD_ITEM*>::iterator it;
	for( it=lookupTable.begin(); it != lookupTable.end(); it++ )
	{
		if( (*it)->GetInternalName() == internalName )
		{
			return *it;
		}
	}
	return NULL;
}

BG_BUILD_ITEM *BG_BUILD_INSTANCE::FillBaseData()
{
	if( itemID < 0 )
		return NULL;
	return itmm->ItemLookup( itemID );
}