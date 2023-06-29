#pragma once
#include "CoreMinimal.h"

class APlayerCharacter;
class APickableActor;
class PlayerStorage;

class SHADOW_WEAVER_API GameCharacterManager
{
private:
	GameCharacterManager();
public:
	~GameCharacterManager();
public:
	static GameCharacterManager* GetInstance();

	void SetMainPlayer(APlayerCharacter* _mainPlayer);
	APlayerCharacter* GetMainPlayer();

	void SetCharacterStorage(PlayerStorage* _playerStorage);
	PlayerStorage* GetCharacterStorage();

	void SetPickableActor(APickableActor* m_tmpActor);
	APickableActor* GetPickableActor();

	bool bDebugFlag;
private:
	APickableActor* m_tmpPickableActor;
	APlayerCharacter* m_mainplayer;
	PlayerStorage* m_playerStorage;
	static GameCharacterManager* m_instance;
};
