#pragma once

#include "CoreMinimal.h"

class FJsonObject;

class SHADOW_WEAVER_API GameItem
{
public:
	GameItem();
	~GameItem();


public:
	void SetId(int _id);
	int GetId();
	virtual void Parse(const TSharedPtr<FJsonObject>& _jsonObject);

private:
	int m_id;

};
