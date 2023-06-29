#include "PlayerStorage.h"
#include "../Utils/FileUtils.h"

void PlayerStorage::AddToStorage(int _key, int _value)
{

	auto itr = this->m_PlayerStorage.find(_key);

	if (itr != this->m_PlayerStorage.end())
	{
		itr->second += _value;
	}
	else
	{
		this->m_PlayerStorage.insert(std::make_pair(_key, _value));
	}
}

void PlayerStorage::RemoveFromStorage(int _key, int _value)
{
	auto itr = this->m_PlayerStorage.find(_key);

	if (itr != this->m_PlayerStorage.end())
	{
		if (itr->second > _value)
		{
			itr->second -= _value;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Trying to spend more then have")); // Check Error
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to spend mon-existent subject")); // Check Error
	}

}

int PlayerStorage::SearchByID(int _key)
{
	auto itr = this->m_PlayerStorage.find(_key);

	if (itr != this->m_PlayerStorage.end())
	{
		return itr->second;
	}
	else
	{
		return -1;
	}
}

void PlayerStorage::ParseItems(TSharedPtr<FJsonObject>& _jsonObject)
{
}

PlayerStorage::PlayerStorage()
{
}

PlayerStorage::~PlayerStorage()
{
}
