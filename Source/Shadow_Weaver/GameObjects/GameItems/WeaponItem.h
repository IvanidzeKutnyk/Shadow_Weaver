#pragma once

#include "CoreMinimal.h"
#include "GameItem.h"

enum class WeaponParams
{
	NONE,
	ONE_HANDED,	//--TYPE	
	TWO_HANDED,	//--TYPE
	SPECIAL,	//--TYPE

	AXE			//--CATEGORY
};

class SHADOW_WEAVER_API WeaponItem : public GameItem

{
public:
	WeaponItem();
	~WeaponItem();

public:
	void Parse(const TSharedPtr<FJsonObject>& _jsonObject) override;

private:
	WeaponParams m_Type;
	WeaponParams m_Category;
	FString m_Name;
	float m_Damage;
	float m_Speed;
	float m_Block;
	float m_Aftereffect;
};
