#include "GameItemsManager.h"
#include "../Utils/FileUtils.h"
#include "../GameObjects/GameItems/AnimalItem.h"
#include "../GameObjects/GameItems/ArmorItem.h"
#include "../GameObjects/GameItems/MoneyItem.h"
#include "../GameObjects/GameItems/ResourceItem.h"
#include "../GameObjects/GameItems/WeaponItem.h"
#include "../GameObjects/Player/PlayerCharacter.h"

GameItemsManager* GameItemsManager::m_instance = nullptr;

void GameItemsManager::ParseItems()
{
	const FString filePath = "C:/Unreal/MainGameProject/Shadow_Weaver/Data/GameObjects.json";
	TSharedPtr<FJsonObject> jsonObject = FileUtils::ReadJson(filePath);

	const TArray<TSharedPtr<FJsonValue>>* GameItems = nullptr;
	const TArray<TSharedPtr<FJsonValue>>* tempItems = nullptr;
	 
	if (jsonObject->TryGetArrayField("GameItems", GameItems))
	{
		for (const TSharedPtr<FJsonValue>& GameItemValue : *(GameItems))
		{
			TSharedPtr<FJsonObject> GameItemObject = GameItemValue->AsObject();

			if (GameItemObject->TryGetArrayField("AnimalItem", tempItems))
			{
				for (const TSharedPtr<FJsonValue>& AnimalItemValue : *(tempItems))
				{
					GameItem * Animal = new AnimalItem();
					Animal->Parse(AnimalItemValue->AsObject());
					m_items.push_back(Animal);
				}
			}
			if (GameItemObject->TryGetArrayField("WeaponItem", tempItems))
			{
				for (const TSharedPtr<FJsonValue>& WeaponItemValue : *(tempItems))
				{
					GameItem* Weapon = new WeaponItem();
					Weapon->Parse(WeaponItemValue->AsObject());
					m_items.push_back(Weapon);

				}
			}
			if (GameItemObject->TryGetArrayField("ArmorItem", tempItems))
			{
				for (const TSharedPtr<FJsonValue>& ArmorItemValue : *(tempItems))
				{
					GameItem* Armor = new ArmorItem();
					Armor->Parse(ArmorItemValue->AsObject());
					m_items.push_back(Armor);

				}
			}
			if (GameItemObject->TryGetArrayField("MoneyItem", tempItems))
			{
				for (const TSharedPtr<FJsonValue>& MoneyItemValue : *(tempItems))
				{
					GameItem* Money = new MoneyItem();
					Money->Parse(MoneyItemValue->AsObject());
					m_items.push_back(Money);
				}
			}
			if (GameItemObject->TryGetArrayField("ResourceItem", tempItems))
			{
				for (const TSharedPtr<FJsonValue>& ResourceItemValue : *(tempItems))
				{
					GameItem* Resource = new ResourceItem();
					Resource->Parse(ResourceItemValue->AsObject());
					m_items.push_back(Resource);

				}
			}
		}
	}
}

GameItemsManager::GameItemsManager()
{
	this->m_items.reserve(10); // RESERVE VECTOR
}

GameItemsManager* GameItemsManager::GetInstance()
{
	if (m_instance == nullptr) 
	{
		m_instance = new GameItemsManager();
	}
	return m_instance;
}

GameItemsManager::~GameItemsManager()
{

}