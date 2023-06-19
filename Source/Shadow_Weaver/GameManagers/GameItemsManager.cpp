#include "GameItemsManager.h"
#include "../Utils/FileUtils.h"

void GameItemsManager::ParseItems()
{
	const FString filePath = "C:/Unreal/MainGameProject/Shadow_Weaver/Data/GameObjects.json";
	TSharedPtr<FJsonObject> jsonObject = FileUtils::ReadJson(filePath);

	for (auto& jsonPairs : jsonObject->Values) 
	{
		//const FString& Key = jsonPairs.Key;
		//const TSharedPtr<FJsonValue>& Value = JsonPair.Value;
	}
}

GameItemsManager::GameItemsManager()
{
	this->m_items.reserve(10); // RESERVE VECTOR
}

GameItemsManager::~GameItemsManager()
{

}
