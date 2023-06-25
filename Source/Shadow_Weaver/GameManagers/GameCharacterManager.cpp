#include "GameCharacterManager.h"
#include "../GameObjects/Player/PlayerCharacter.h"

GameCharacterManager* GameCharacterManager::m_instance = nullptr;

GameCharacterManager::GameCharacterManager()
	: m_interact(false)
	, m_tmpPickableActor(nullptr)
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

void GameCharacterManager::SetInteractable(bool _interact)
{
	this->m_interact = _interact;
}

bool GameCharacterManager::GetInteractable()
{
	return m_interact;
}

void GameCharacterManager::SetPickableActor(APickableActor* m_tmpActor)
{
	this->m_tmpPickableActor = m_tmpActor;
}

APickableActor* GameCharacterManager::GetPickableActor()
{
	return m_tmpPickableActor;
}
