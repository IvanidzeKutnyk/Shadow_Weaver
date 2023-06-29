#include "GameCharacterManager.h"
#include "../GameObjects/Player/PlayerCharacter.h"

GameCharacterManager* GameCharacterManager::m_instance = nullptr;

GameCharacterManager::GameCharacterManager()
	: m_tmpPickableActor(nullptr)
	, bDebugFlag(true)
{
}

GameCharacterManager::~GameCharacterManager()
{
}

GameCharacterManager* GameCharacterManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new GameCharacterManager();
	}
	return m_instance;
}

void GameCharacterManager::SetMainPlayer(APlayerCharacter* _mainplayer)
{
	this->m_mainplayer = _mainplayer;
}

APlayerCharacter* GameCharacterManager::GetMainPlayer()
{
	return this->m_mainplayer;
}

void GameCharacterManager::SetCharacterStorage(PlayerStorage* _playerStorage)
{
	this->m_playerStorage = _playerStorage;
}

PlayerStorage* GameCharacterManager::GetCharacterStorage()
{
	return this->m_playerStorage;
}

void GameCharacterManager::SetPickableActor(APickableActor* m_tmpActor)
{
	this->m_tmpPickableActor = m_tmpActor;
}

APickableActor* GameCharacterManager::GetPickableActor()
{
	return m_tmpPickableActor;
}
