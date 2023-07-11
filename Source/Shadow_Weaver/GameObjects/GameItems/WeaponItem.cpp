// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "../../Utils/DebugSystem.h"

void WeaponItem::Parse(const TSharedPtr<FJsonObject>& _jsonObject)
{
	FString _tempWeaponParams;

	//---ID---//
	GameItem::Parse(_jsonObject);
	//---Type---//
	_jsonObject->TryGetStringField("Type", _tempWeaponParams);
	if (_tempWeaponParams == "OneHand") 
	{
		this->m_Type = WeaponParams::ONE_HANDED;
	}
	else if (_tempWeaponParams == "TwoHand")
	{
		this->m_Type = WeaponParams::TWO_HANDED;
	}
	else if (_tempWeaponParams == "Special")
	{
		this->m_Type = WeaponParams::SPECIAL;
	}
	//---Category---//
	_jsonObject->TryGetStringField("Category", _tempWeaponParams);
	if (_tempWeaponParams == "Axe")
	{
		this->m_Type = WeaponParams::AXE;
	}
	else if (_tempWeaponParams == "TwoHand")
	{
		this->m_Type = WeaponParams::TWO_HANDED;
	}
	else if (_tempWeaponParams == "Special")
	{
		this->m_Type = WeaponParams::SPECIAL;
	}
	//---Name---//
	_jsonObject->TryGetStringField("Name", this->m_Name);
	//---Damage---//
	_jsonObject->TryGetNumberField("Damage", this->m_Damage);
	//---Speed---//
	_jsonObject->TryGetNumberField("Speed", this->m_Speed);
	//---Block---//
	_jsonObject->TryGetNumberField("Block", this->m_Block);
	//---AfterEffect---//
	_jsonObject->TryGetNumberField("AfterEffect", this->m_Aftereffect);
}

WeaponItem::WeaponItem() : GameItem()
{

}

WeaponItem::~WeaponItem()
{
}
