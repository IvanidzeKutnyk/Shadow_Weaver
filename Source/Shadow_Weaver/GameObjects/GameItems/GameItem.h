#pragma once

#include "CoreMinimal.h"

class SHADOW_WEAVER_API GameItem
{
private:
	int m_id;
public:
	void SetId(int _id);
	int GetId();
	virtual void Parse();
public:
	GameItem();
	~GameItem();
};
