#pragma once

#include "CoreMinimal.h"
#include "GameItem.h"


class SHADOW_WEAVER_API AnimalItem : public GameItem
{
public:
	AnimalItem();
	~AnimalItem();
	
	void Parse(const TSharedPtr<FJsonObject>& _jsonObject) override;
};
