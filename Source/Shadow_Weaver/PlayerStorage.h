#pragma once

#include <iostream>
#include <map>
#include "CoreMinimal.h"

class SHADOW_WEAVER_API PlayerStorage
{
private:
	std::map<int, int> m_PlayerStorage;



public:
	void AddToStorage(int _key, int _value);
	void RemoveFromStorage(int _key, int _value);

public:
	PlayerStorage();
	~PlayerStorage();
};
