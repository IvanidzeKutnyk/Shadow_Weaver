#pragma once
#include "CoreMinimal.h"

class APlayerCharacter;
class APickableActor;

class SHADOW_WEAVER_API GameCharacterManager
{
private:
	GameCharacterManager();
public:
	~GameCharacterManager();
public:
	static GameCharacterManager* GetInstance();
	void SetMainPlayer(APlayerCharacter* _mainplayer);
	APlayerCharacter* GetMainPlayer();

	void SetInteractable(bool _interact);
	bool GetInteractable();
	void SetPickableActor(APickableActor* m_tmpActor);
	APickableActor* GetPickableActor();
private:
	APickableActor* m_tmpPickableActor;
	static GameCharacterManager* m_instance;
	APlayerCharacter* m_mainplayer;
	bool m_interact;
};
