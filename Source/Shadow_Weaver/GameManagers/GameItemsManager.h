#pragma once

#include "CoreMinimal.h"
#include <vector>

class GameItem;
class APlayerCharacter;

class SHADOW_WEAVER_API GameItemsManager
{
private:
	GameItemsManager();
public:
	~GameItemsManager();


public:
	static GameItemsManager* GetInstance();
	void ParseItems();

private:
	static GameItemsManager* m_instance;
	std::vector <GameItem*> m_items;
};
