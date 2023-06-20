#pragma once

#include "CoreMinimal.h"
#include "GameItem.h"

class SHADOW_WEAVER_API WeaponItem : public GameItem

{
public:
	WeaponItem();
	~WeaponItem();

public:
	void Parse(const TSharedPtr<FJsonObject>& _jsonObject) override;

public:
	enum class WeaponType
	{
		ONE_HANDED,
		TWO_HANDED,
		SPECIAL
	};
};
