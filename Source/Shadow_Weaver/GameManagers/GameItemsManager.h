#pragma once

#include "CoreMinimal.h"
#include <vector>

class GameItem;

class SHADOW_WEAVER_API GameItemsManager
{
private:
	std::vector <GameItem*> m_items;
public:
	void ParseItems();
public:
	GameItemsManager();
	~GameItemsManager();
};
